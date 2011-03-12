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
	net::port_type const _port
)
:
	resources_(
		_resources
	),
	port_(
		_port
	),
	net_(
		net::server::time_resolution(
			16
		)
	),
	s_conn(
		net_.register_connect(
			std::tr1::bind(
				&machine::connect_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	s_disconn(
		net_.register_disconnect(
			std::tr1::bind(
				&machine::disconnect_callback,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	s_data(
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
	tick_event const &t
)
{
	BOOST_FOREACH(client_map::reference ref, clients_)
	{
		net::data_type &buffer = ref.second.out_buffer;
		if (buffer.size())
		{
			net_.queue(ref.first, buffer);
			buffer.clear();
		}
	}

	process_event(t);
}

void
sanguis::server::machine::run()
{
	net_.run();
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
	net::id_type const _id
)
{
	clients_.insert(
		_id,
		client_data()
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
	net::id_type const _id,
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
	net::id_type const _id,
	messages::auto_ptr _m
)
{
	process_event(
		message_event(
			_m,
			_id
		)
	);
}

void
sanguis::server::machine::data_callback(
	net::id_type const _id,
	net::data_type const &_data
)
{
	fcppt::algorithm::append(
		clients_[_id].in_buffer,
		_data
	);

	for(;;)
	{
		messages::auto_ptr p = 
			net::deserialize(
				clients_[_id].in_buffer
			);

		if(!p.get())
			return;

		process_message(_id, p);
	}
}

void
sanguis::server::machine::send_to_all(
	messages::auto_ptr _m
)
{ 
	net::data_type m_str;

	net::serialize(
		_m,
		m_str
	);

	BOOST_FOREACH(
		client_map::reference ref,
		clients_
	)
		fcppt::algorithm::append(
			ref.second.out_buffer,
			m_str
		);
}

sanguis::net::port_type
sanguis::server::machine::port() const
{
	return 
		port_;
}

sanguis::net::server &
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
	net::id_type const _id,
	messages::auto_ptr _m
)
try
{
	net::data_type ser;

	net::serialize(
		_m,
		ser
	);

	fcppt::algorithm::append(
		clients_[_id].out_buffer,
		ser
	);
}
catch(
	fcppt::exception const &e
)
{
	FCPPT_LOG_ERROR(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("send_unicast failed: ")
			<< e.string()
	);
}
