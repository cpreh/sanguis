#include <sanguis/server/machine.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/serialize_to_circular_buffer.hpp>
#include <sanguis/net/serialize_to_data_buffer.hpp>
#include <sanguis/net/deserialize.hpp>
#include <sanguis/net/server/connection_id_container.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/move.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::server::machine::machine(
	load::context_base const &_resources,
	sge::charconv::system &_charconv_system,
	net::port const _port,
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
	net_(
		_io_service,
		boost::chrono::milliseconds(
			16
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
	s_timer_(
		net_.register_timer(
			std::tr1::bind(
				std::tr1::bind(
					&machine::timer_callback,
					this
				)
			)
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
	net_.stop();
}

void
sanguis::server::machine::send_to_all(
	messages::base const &_message
)
{
	temp_buffer_.clear();

	net::serialize_to_data_buffer(
		_message,
		temp_buffer_
	);

	net::server::connection_id_container const &connections(
		net_.connections()
	);

	for(
		net::server::connection_id_container::const_iterator it(
			connections.begin()
		);
		it != connections.end();
		++it
	)
	{
		net::id const id(
			*it
		);

		if(
			!net::append_to_circular_buffer(
				*net_.send_buffer(
					id
				),
				temp_buffer_
			)
		)
		{
			FCPPT_LOG_ERROR(
				server::log(),
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
	server::player_id const _id,
	messages::base const &_message
)
{
	net::id const net_id(
		_id.get()
	);

	net::circular_buffer *const buffer(
		net_.send_buffer(
			net_id
		)
	);

	if(
		!buffer
	)
	{
		FCPPT_LOG_ERROR(
			server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Client ")
				<< net_id
				<< FCPPT_TEXT(" is gone.")
		);

		return;
	}

	if(
		!net::serialize_to_circular_buffer(
			_message,
			*buffer
		)
	)
	{
		FCPPT_LOG_ERROR(
			server::log(),
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
	net::id const _id,
	messages::auto_ptr _message
)
{
	FCPPT_LOG_VERBOSE(
		server::log(),
		fcppt::log::_
			<< FCPPT_TEXT("process_message")
	);

	this->process_event(
		events::message(
			fcppt::move(
				_message
			),
			_id
		)
	);
}

void
sanguis::server::machine::connect_callback(
	net::id const _id
)
{
	// WTF
}

void
sanguis::server::machine::disconnect_callback(
	net::id const _id,
	fcppt::string const &
)
{
	this->process_event(
		events::disconnect(
			_id
		)
	);
}

void
sanguis::server::machine::data_callback(
	net::id const _id,
	net::receive_buffer &_data
)
{
	for(;;)
	{
		messages::auto_ptr message(
			net::deserialize(
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
		events::tick(
			sge::timer::elapsed_and_reset<
				sanguis::duration
			>(
				frame_timer_
			)
		)
	);
}
