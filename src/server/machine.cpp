#include "machine.hpp"
#include "log.hpp"
#include "events/disconnect.hpp"
#include "events/message.hpp"
#include "events/tick.hpp"
#include "../messages/auto_ptr.hpp"
#include "../messages/base.hpp"
#include "../net/append_to_circular_buffer.hpp"
#include "../net/serialize_to_circular_buffer.hpp"
#include "../net/serialize_to_data_buffer.hpp"
#include "../net/deserialize.hpp"
#include "../exception.hpp"
#include <sge/time/millisecond.hpp>
#include <sge/time/second.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

sanguis::server::machine::machine(
	load::context_base const &_resources,
	net::port const _port,
	awl::mainloop::io_service &_io_service
)
:
	resources_(
		_resources
	),
	port_(
		_port
	),
	net_(
		_io_service,
		sge::time::millisecond(
			16
		)
	),
	frame_timer_(
		sge::time::second(
			1
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
	),
	clients_()
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
	messages::auto_ptr _message
)
{
	temp_buffer_.clear();

	net::serialize_to_data_buffer(
		_message,
		temp_buffer_
	);

	BOOST_FOREACH(
		client_set::value_type id,
		clients_
	)
	{
		if(
			!net::append_to_circular_buffer(
				net_.send_buffer(
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
	messages::auto_ptr _message
)
{
	net::id const net_id(
		_id.get()
	);

	if(
		!net::serialize_to_circular_buffer(
			_message,
			net_.send_buffer(
				net_id
			)
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

void
sanguis::server::machine::process_message(
	net::id const _id,
	messages::auto_ptr _message
)
{
	FCPPT_LOG_DEBUG(
		server::log(),
		fcppt::log::_
			<< FCPPT_TEXT("process_message")
	);

	this->process_event(
		events::message(
			_message,
			_id
		)
	);
}

void
sanguis::server::machine::connect_callback(
	net::id const _id
)
{
	if(
		!clients_.insert(
			_id
		).second
	)
		throw sanguis::exception(
			FCPPT_TEXT("Client inserted twice in server!")
		);
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

	clients_.erase(
		_id
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
			message
		);
	}
}

void
sanguis::server::machine::timer_callback()
{
	this->process_event(
		events::tick(
			static_cast<
				time_type
			>(
				frame_timer_.reset()
			)
		)
	);
}
