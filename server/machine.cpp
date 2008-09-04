#include "machine.hpp"
#include "../tick_event.hpp"
#include "../serialization.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "message_event.hpp"

#include <sge/systems.hpp>

#include <boost/bind.hpp>

sanguis::server::machine::machine(
	sge::systems &sys,
	sge::con::console_gfx &con,
	const net::port_type port_)
: port_(port_),
  s_conn(net_.register_connect(boost::bind(&machine::connect_callback,this,_1))),
  s_disconn(
  	net_.register_disconnect(boost::bind(&machine::disconnect_callback,this,_1,_2))),
  s_data(net_.register_data(boost::bind(&machine::data_callback,this,_1,_2))),
  resource_connection(
  	sys.image_loader,
	sys.renderer),
	con(con)
{}

void sanguis::server::machine::console_print(const sge::string &s)
{
	con.print(s);
}

void sanguis::server::machine::process(const tick_event &t)
{
	for (client_map::iterator i = clients.begin(); i != clients.end(); ++i)
	{
		net::data_type &buffer = i->second.out_buffer;
		if (buffer.size())
		{
			net_.queue(i->first,buffer);
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

void sanguis::server::machine::connect_callback(const net::id_type id)
{
	process_event(
		message_event(
			messages::auto_ptr(
				new messages::connect),
			id));
}

void sanguis::server::machine::disconnect_callback(const net::id_type id,
	const net::string_type &)
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

void sanguis::server::machine::data_callback(const net::id_type id,
	const net::data_type &data)
{
	clients[id].in_buffer = deserialize(clients[id].in_buffer+data,boost::bind(&machine::process_message,this,id,_1));
}

void sanguis::server::machine::send(
	messages::auto_ptr m) 
{ 
	const net::data_type m_str = serialize(m);
	for (client_map::iterator i = clients.begin(); i != clients.end(); ++i)
		i->second.out_buffer += m_str;
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
