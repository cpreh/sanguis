#include "machine.hpp"
#include "message_event.hpp"
#include "../tick_event.hpp"
#include "../messages/create.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../net/serialize.hpp"
#include "../net/deserialize.hpp"
#include "../exception.hpp"
#include "../log.hpp"
#include <fcppt/algorithm/append.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

sanguis::server::machine::machine(
	load::context_base const &_resources,
	sge::collision::system_ptr const _collision,
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
		_io_service
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
	clients_(),
	collision_(_collision)
{
}

sanguis::server::machine::~machine()
{
}

void
sanguis::server::machine::process(
	tick_event const &_event
)
{
	this->process_event(
		_event
	);
}

void
sanguis::server::machine::stop()
{
	net_.stop();
}

void
sanguis::server::machine::listen()
{
	net_.listen(
		port_
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

	process_event(
		message_event(
			messages::create(
				messages::connect()
			),
			_id
		)
	);
}

void
sanguis::server::machine::disconnect_callback(
	net::id const _id,
	fcppt::string const &
)
{
	process_event(
		message_event(
			messages::create(
				messages::disconnect()
			),
			_id
		)
	);

	clients_.erase(
		_id
	);
}

void
sanguis::server::machine::process_message(
	net::id const _id,
	messages::auto_ptr _message
)
{
	process_event(
		message_event(
			_message,
			_id
		)
	);
}

void
sanguis::server::machine::data_callback(
	net::id const _id,
	net::data_buffer &_data
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
sanguis::server::machine::send_to_all(
	messages::auto_ptr _message
)
{ 
	this->pack_message(
		_message
	);

	BOOST_FOREACH(
		client_set::value_type id,
		clients_
	)
		net_.queue(
			id,
			temp_buffer_
		);

	temp_buffer_.clear();
}

sanguis::net::port
sanguis::server::machine::port() const
{
	return 
		port_;
}

sanguis::net::server::object &
sanguis::server::machine::net()
{
	return 
		net_;
}

sanguis::load::context_base const &
sanguis::server::machine::resources() const
{
	return 
		resources_;
}

sge::collision::system_ptr const
sanguis::server::machine::collision_system() const
{
	return 
		collision_;
}

void
sanguis::server::machine::send_unicast(
	net::id const _id,
	messages::auto_ptr _message
)
try
{
	this->pack_message(
		_message
	);

	net_.queue(
		_id,
		temp_buffer_	
	);

	temp_buffer_.clear();
}
catch(
	fcppt::exception const &_error
)
{
	FCPPT_LOG_ERROR(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("send_unicast failed: ")
			<< _error.string()
	);
}

void
sanguis::server::machine::pack_message(
	messages::auto_ptr _message
)
{
	FCPPT_ASSERT(
		temp_buffer_.empty()
	);

	net::serialize(
		_message,
		temp_buffer_
	);
}
