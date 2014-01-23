#include <sanguis/duration.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/load/server_context.hpp>
#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/receive_buffer_size.hpp>
#include <sanguis/net/send_buffer_size.hpp>
#include <sanguis/net/client/deserialize.hpp>
#include <sanguis/net/server/serialize_to_circular_buffer.hpp>
#include <sanguis/net/server/serialize_to_data_buffer.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <alda/net/id.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <alda/net/buffer/circular_send/optional_ref.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::machine::machine(
	alda::net::port const _port,
	sanguis::io_service &_io_service
)
:
	resources_(),
	port_(
		_port
	),
	io_service_(
		_io_service
	),
	net_(
		alda::net::parameters(
			io_service_.impl(),
			sanguis::net::send_buffer_size(),
			sanguis::net::receive_buffer_size()
		)
	),
	frame_timer_(
		sanguis::timer::parameters(
			std::chrono::seconds(
				1
			)
		)
	),
	temp_buffer_(),
	disconnect_connection_(
		net_.register_disconnect(
			std::bind(
				&sanguis::server::machine::disconnect_callback,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		)
	),
	data_connection_(
		net_.register_data(
			std::bind(
				&sanguis::server::machine::data_callback,
				this,
				std::placeholders::_1,
				std::placeholders::_2
			)
		)
	),
	timer_(
		io_service_,
		std::bind(
			std::bind(
				&sanguis::server::machine::timer_callback,
				this
			)
		),
		std::chrono::milliseconds(
			16
		)
	)
{
}

sanguis::server::machine::~machine()
{
}

void
sanguis::server::machine::listen()
{
	net_.listen(
		port_
	);
}

void
sanguis::server::machine::send_to_all(
	sanguis::messages::server::base const &_message
)
{
	temp_buffer_.clear();

	sanguis::net::server::serialize_to_data_buffer(
		_message,
		temp_buffer_
	);

	alda::net::server::connection_id_container const &connections(
		net_.connections()
	);

	for(
		auto const &id
		:
		connections
	)
	{
		if(
			!sanguis::net::append_to_circular_buffer(
				*net_.send_buffer(
					id
				),
				temp_buffer_
			)
		)
		{
			FCPPT_LOG_ERROR(
				sanguis::server::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Client ")
					<< id
					<< FCPPT_TEXT(" has no space left in machine::send()!")
			);
			// TODO!
			continue;
		}

		net_.queue_send(
			id
		);
	}
}

void
sanguis::server::machine::send_unicast(
	sanguis::server::player_id const _id,
	sanguis::messages::server::base const &_message
)
{
	alda::net::id const net_id(
		_id.get()
	);

	alda::net::buffer::circular_send::optional_ref const buffer(
		net_.send_buffer(
			net_id
		)
	);

	if(
		!buffer
	)
	{
		FCPPT_LOG_ERROR(
			sanguis::server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Client ")
				<< net_id
				<< FCPPT_TEXT(" is gone.")
		);

		return;
	}

	if(
		!sanguis::net::server::serialize_to_circular_buffer(
			_message,
			*buffer
		)
	)
	{
		FCPPT_LOG_ERROR(
			sanguis::server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Client ")
				<< net_id
				<< FCPPT_TEXT(" has no space left in machine::send_unicast()!")
		);

		// TODO!
		return;
	}

	net_.queue_send(
		net_id
	);
}

sanguis::load::server_context const &
sanguis::server::machine::resources() const
{
	return
		resources_;
}

void
sanguis::server::machine::process_message(
	alda::net::id const _id,
	sanguis::messages::client::unique_ptr &&_message
)
{
	FCPPT_LOG_VERBOSE(
		sanguis::server::log(),
		fcppt::log::_
			<< FCPPT_TEXT("process_message")
	);

	this->process_event(
		sanguis::server::events::message(
			std::move(
				_message
			),
			sanguis::server::player_id_from_net(
				_id
			)
		)
	);
}

void
sanguis::server::machine::disconnect_callback(
	alda::net::id const _id,
	fcppt::string const &
)
try
{

	this->process_event(
		sanguis::server::events::disconnect(
			_id
		)
	);
}
catch(
	fcppt::exception const &_error
)
{
	FCPPT_LOG_ERROR(
		sanguis::server::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Player disconnected: ")
			<< _error.string()
	);
}

void
sanguis::server::machine::data_callback(
	alda::net::id const _id,
	alda::net::buffer::circular_receive::object &_data
)
try
{
	for(
		;;
	)
	{
		sanguis::messages::client::unique_ptr message(
			sanguis::net::client::deserialize(
				_data
			)
		);

		if(
			!message.get()
		)
			return;

		this->process_message(
			_id,
			std::move(
				message
			)
		);
	}
}
catch(
	fcppt::exception const &_error
)
{
	this->disconnect_callback(
		_id,
		_error.string()
	);
}
catch(
	...
)
{
	this->disconnect_callback(
		_id,
		FCPPT_TEXT("Unknown error")
	);
}

void
sanguis::server::machine::timer_callback()
{
	this->process_event(
		sanguis::server::events::tick(
			sge::timer::elapsed_and_reset<
				sanguis::duration
			>(
				frame_timer_
			)
		)
	);
}
