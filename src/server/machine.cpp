#include <sanguis/duration.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/load/context_base_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/receive_buffer_size.hpp>
#include <sanguis/net/send_buffer_size.hpp>
#include <sanguis/net/serialize_to_circular_buffer.hpp>
#include <sanguis/net/serialize_to_data_buffer.hpp>
#include <sanguis/net/deserialize.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <alda/net/id.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <alda/net/buffer/circular_send/optional_ref.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <fcppt/move.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::machine::machine(
	sanguis::load::context_base const &_resources,
	sge::charconv::system &_charconv_system,
	alda::net::port const _port,
	sanguis::io_service &_io_service
)
:
	resources_(
		_resources
	),
	charconv_system_(
		_charconv_system
	),
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
			boost::chrono::seconds(
				1
			)
		)
	),
	temp_buffer_(),
	s_conn_(
		net_.register_connect(
			std::tr1::bind(
				&machine::connect_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	s_disconn_(
		net_.register_disconnect(
			std::tr1::bind(
				&machine::disconnect_callback,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	s_data_(
		net_.register_data(
			std::tr1::bind(
				&machine::data_callback,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	timer_(
		io_service_,
		std::tr1::bind(
			std::tr1::bind(
				&machine::timer_callback,
				this
			)
		),
		boost::chrono::milliseconds(
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
sanguis::server::machine::stop()
{
	io_service_.stop();
}

void
sanguis::server::machine::send_to_all(
	sanguis::messages::base const &_message
)
{
	temp_buffer_.clear();

	sanguis::net::serialize_to_data_buffer(
		_message,
		temp_buffer_
	);

	alda::net::server::connection_id_container const &connections(
		net_.connections()
	);

	for(
		alda::net::server::connection_id_container::const_iterator it(
			connections.begin()
		);
		it != connections.end();
		++it
	)
	{
		alda::net::id const id(
			*it
		);

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
	sanguis::messages::base const &_message
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
		!sanguis::net::serialize_to_circular_buffer(
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

sanguis::load::context_base const &
sanguis::server::machine::resources() const
{
	return
		resources_;
}

sge::charconv::system &
sanguis::server::machine::charconv_system() const
{
	return
		charconv_system_;
}

void
sanguis::server::machine::process_message(
	alda::net::id const _id,
	sanguis::messages::auto_ptr _message
)
{
	FCPPT_LOG_VERBOSE(
		sanguis::server::log(),
		fcppt::log::_
			<< FCPPT_TEXT("process_message")
	);

	this->process_event(
		sanguis::server::events::message(
			fcppt::move(
				_message
			),
			_id
		)
	);
}

void
sanguis::server::machine::connect_callback(
	alda::net::id const _id
)
{
	// WTF
}

void
sanguis::server::machine::disconnect_callback(
	alda::net::id const _id,
	fcppt::string const &
)
{
	this->process_event(
		sanguis::server::events::disconnect(
			_id
		)
	);
}

void
sanguis::server::machine::data_callback(
	alda::net::id const _id,
	alda::net::buffer::circular_receive::object &_data
)
{
	for(;;)
	{
		sanguis::messages::auto_ptr message(
			sanguis::net::deserialize(
				_data
			)
		);

		if(
			!message.get()
		)
			return;

		this->process_message(
			_id,
			fcppt::move(
				message
			)
		);
	}
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
