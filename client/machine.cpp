#include "machine.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../serialization.hpp"
#include "message_event.hpp"
#include <sge/renderer/scoped_renderblock.hpp>
#include <sge/renderer/scoped_state.hpp>
#include <boost/spirit/phoenix.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/construct.hpp>

sanguis::client::machine::machine(sge::systems &sys,sge::font &font,sge::key_state_tracker &ks,sge::con::console_gfx &con,
	const net::address_type &address_,const net::port_type port_) 
	: address_(address_),port_(port_),
	  s_conn(net_.register_connect(boost::bind(&machine::connect_callback,this))),
	  s_disconn(
			net_.register_disconnect(boost::bind(&machine::disconnect_callback,this,_1))),
		s_data(net_.register_data(boost::bind(&machine::data_callback,this,_1))),
		sys(sys),font(font),ks(ks),con(con),con_wrapper(con,sys.input_system,sge::kc::key_tab),resource(sys.image_loader,sys.renderer) {}

void sanguis::client::machine::connect()
{
	net_.connect(address_,port_);
}

void sanguis::client::machine::connect_callback()
{
	process_event(message_event(message_ptr(new messages::connect)));
}

void sanguis::client::machine::disconnect_callback(const net::string_type &)
{
	process_event(message_event(message_ptr(new messages::disconnect)));
}

void sanguis::client::machine::process_message(const message_ptr ptr)
{
	process_event(message_event(ptr));
}

void sanguis::client::machine::data_callback(const net::data_type &data)
{
	in_buffer = deserialize(in_buffer+data,boost::bind(&machine::process_message,this,_1));
}

void sanguis::client::machine::queue_internal(const message_event &m)
{
	message_events.push(m);
}

void sanguis::client::machine::send(messages::base *const m)
{
	out_buffer += serialize(message_ptr(m));
}

bool sanguis::client::machine::process(const tick_event &t)
{
	while (!message_events.empty())
	{
		process_event(message_events.front());
		message_events.pop();
	}
	
	if (out_buffer.size())
	{
		net_.queue(out_buffer);
		out_buffer.clear();
	}

	net_.process();

	const sge::scoped_renderblock block_(sys.renderer);
	sys.renderer->set_state((sge::bool_state::clear_backbuffer=true));
	process_event(t);

	if (con.active())
		con.draw();

	return !ks[sge::kc::key_escape];
}
