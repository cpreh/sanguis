#include "machine.hpp"
#include "../tick_event.hpp"
#include "../serialization.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../exception.hpp"
#include "message_event.hpp"

#include <sge/console/console_gfx.hpp>
#include <sge/systems/instance.hpp>
#include <sge/text.hpp>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

sanguis::server::machine::machine(
	load::context const &resources_,
	sge::collision::system_ptr const _collision,
	sge::con::console_gfx &con,
	net::port_type const port_)
:
	resources_(
		resources_),
	port_(
		port_),
	s_conn(
		net_.register_connect(
			boost::bind(
				&machine::connect_callback,
				this,
				_1))),
	s_disconn(
		net_.register_disconnect(
			boost::bind(
				&machine::disconnect_callback,
				this,
				_1,
				_2))),
	s_data(
		net_.register_data(
			boost::bind(
				&machine::data_callback,
				this,
				_1,
				_2))),
	collision_(_collision),
	con(con)
{}

void sanguis::server::machine::console_print(
	sge::string const &s)
{
	con.print(s);
}

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
	process_event(
		message_event(
			messages::auto_ptr(
				new messages::connect),
			id));
}

void sanguis::server::machine::disconnect_callback(
	net::id_type const id,
	net::string_type const &)
{
	process_event(
		message_event(
			messages::auto_ptr(
				new messages::disconnect),
			id));
}

void sanguis::server::machine::process_message(
	net::id_type const id,
	messages::auto_ptr m)
{
	process_event(
		message_event(
			m,
			id));
}

void sanguis::server::machine::data_callback(
	net::id_type const id,
	net::data_type const &data)
{
	clients[id].in_buffer
		= deserialize(
			clients[id].in_buffer + data,
			boost::bind(
				&machine::process_message,
				this,
				id,
				_1));
}

void sanguis::server::machine::send(
	messages::auto_ptr m) 
{ 
	net::data_type const m_str = serialize(m);

	BOOST_FOREACH(client_map::reference ref, clients)
		ref.second.out_buffer += m_str;
}

void sanguis::server::machine::send(
	messages::auto_ptr m,
	net::id_type const dest)
{
	client_map::iterator const it(clients.find(dest));
	if(it == clients.end())
		throw exception(
			SGE_TEXT("machine::send: client id not found!"));
	
	it->second.out_buffer += serialize(m);
}

net::port_type
sanguis::server::machine::port() const
{
	return port_;
}

net::server &
sanguis::server::machine::net()
{
	return net_;
}

sanguis::load::context const &
sanguis::server::machine::resources() const
{
	return resources_;
}

sge::collision::system_ptr const sanguis::server::machine::collision()
{
	return collision_;
}
