#include "machine.hpp"
#include "message_event.hpp"
#include "../tick_event.hpp"
#include "../serialization.hpp"
#include "../messages/create.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../exception.hpp"

#include <sge/console/gfx.hpp>
#include <sge/systems/instance.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/algorithm/append.hpp>
#include <sge/text.hpp>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

sanguis::server::machine::machine(
	load::context const &resources_,
	sge::collision::system_ptr const collision_,
	sge::console::gfx &con,
	net::port_type const port_
)
:
	resources_(
		resources_
	),
	port_(
		port_
	),
	s_conn(
		net_.register_connect(
			boost::bind(
				&machine::connect_callback,
				this,
				_1
			)
		)
	),
	s_disconn(
		net_.register_disconnect(
			boost::bind(
				&machine::disconnect_callback,
				this,
				_1,
				_2
			)
		)
	),
	s_data(
		net_.register_data(
			boost::bind(
				&machine::data_callback,
				this,
				_1,
				_2
			)
		)
	),
	clients(),
	collision_(collision_),
	con(con)
{}

void sanguis::server::machine::process(
	tick_event const &t)
{
	BOOST_FOREACH(client_map::reference ref, clients)
	{
		net::data_type &buffer = ref.second.out_buffer;
		if (buffer.size())
		{
			net_.queue(ref.first, buffer);
			buffer.clear();
		}
	}

	net_.process();
	process_event(t);
}

void sanguis::server::machine::listen()
{
	net_.listen(port_);
}

void sanguis::server::machine::connect_callback(
	net::id_type const id)
{
	clients.insert(
		id,
		client_data()
	);

	process_event(
		message_event(
			messages::create(
				messages::connect()
			),
			id
		)
	);
}

void sanguis::server::machine::disconnect_callback(
	net::id_type const id,
	sge::string const &)
{
	process_event(
		message_event(
			messages::create(
				messages::disconnect()
			),
			id
		)
	);

	clients.erase(
		id
	);
}

void sanguis::server::machine::process_message(
	net::id_type const id,
	messages::auto_ptr m)
{
	process_event(
		message_event(
			m,
			id
		)
	);
}

void sanguis::server::machine::data_callback(
	net::id_type const id,
	net::data_type const &data
)
{
	sge::algorithm::append(
		clients[id].in_buffer,
		data
	);

	for(;;)
	{
		messages::auto_ptr p = deserialize(clients[id].in_buffer);
		if(!p.get())
			return;
		process_message(id, p);
	}
	//while (messages::auto_ptr p = deserialize(clients[id].in_buffer))
	//	process_message(id,p);
}

void sanguis::server::machine::send(
	messages::auto_ptr m
)
{ 
	net::data_type m_str;

	serialize(
		m,
		m_str
	);

	BOOST_FOREACH(
		client_map::reference ref,
		clients
	)
		sge::algorithm::append(
			ref.second.out_buffer,
			m_str
		);
}

sanguis::server::send_callback const
sanguis::server::machine::unicast(
	net::id_type const dest
)
{
	return boost::bind(
		&machine::send_unicast,
		this,
		_1,
		dest
	);
}

sanguis::net::port_type
sanguis::server::machine::port() const
{
	return port_;
}

sanguis::net::server &
sanguis::server::machine::net()
{
	return net_;
}

sanguis::load::context const &
sanguis::server::machine::resources() const
{
	return resources_;
}

sge::collision::world_ptr const
sanguis::server::machine::collision_system() const
{
	return collision_;
}

void
sanguis::server::machine::send_unicast(
	messages::auto_ptr m,
	net::id_type const id)
{
	net::data_type ser;

	serialize(
		m,
		ser
	);

	sge::algorithm::append(
		clients[id].out_buffer,
		ser
	);
}
