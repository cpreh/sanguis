#include "machine.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/add.hpp"
#include "../serialization.hpp"
#include "message_event.hpp"
#include <sge/systems/instance.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/iostream.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/construct.hpp>

sanguis::client::machine::machine(
	load::context const &resources_,
	sge::systems::instance &sys,
	sge::audio::pool &sound_pool_,
	sge::font::object &font_,
	sge::input::key_state_tracker &ks,
	sge::con::console_gfx &con,
	net::address_type const &address_,
	net::port_type const port_) 
:
	resources_(resources_),
	address_(address_),
	port_(port_),
	s_conn(
		net_.register_connect(
			boost::bind(
				&machine::connect_callback,
				this))),
	s_disconn(
		net_.register_disconnect(
			boost::bind(
				&machine::disconnect_callback,
				this,
				_1))),
	s_data(
		net_.register_data(
			boost::bind(
				&machine::data_callback,
				this,
				_1))),
	sys(sys),
	sound_pool_(sound_pool_),
	font_(font_),
	ks(ks),
	con(con),
	con_stdlib(
		boost::bind(
			&sge::con::console_gfx::print,
			&con,
			_1)),
	con_wrapper_(
		con,
		sys.input_system(),
		sge::input::kc::key_f1)
{}

void sanguis::client::machine::connect()
{
	net_.connect(address_,port_);
}

void sanguis::client::machine::connect_callback()
{
	process_event(
		message_event(
			messages::auto_ptr(
				new messages::connect)));
}

void sanguis::client::machine::disconnect_callback(
	net::string_type const &)
{
	process_event(
		message_event(
			messages::auto_ptr(
				new messages::disconnect)));
}

void sanguis::client::machine::process_message(
	messages::auto_ptr ptr)
{
	process_event(
		message_event(
			ptr));
}

void sanguis::client::machine::data_callback(const net::data_type &data)
{
	in_buffer = deserialize(in_buffer+data,boost::bind(&machine::process_message,this,_1));
}

void sanguis::client::machine::send(messages::auto_ptr m)
{
	out_buffer += serialize(m);
}

net::address_type
sanguis::client::machine::address() const
{
	return address_;
}

net::port_type
sanguis::client::machine::port() const
{
	return port_;
}

net::client &
sanguis::client::machine::net()
{
	return net_;
}

bool sanguis::client::machine::process(
	tick_event const &t)
{
	if (out_buffer.size())
	{
		net_.queue(out_buffer);
		out_buffer.clear();
	}

	net_.process();

	sge::renderer::scoped_block const block_(sys.renderer());
	process_event(t);

	if (con.active())
		con.draw();

	return !ks[sge::input::kc::key_escape];
}

void sanguis::client::machine::dispatch()
{
	sge::mainloop::dispatch();
}

sge::renderer::device_ptr const
sanguis::client::machine::renderer() const
{
	return sys.renderer();
}

sge::audio::player_ptr const
sanguis::client::machine::audio_player() const
{
	return sys.audio_player();
}

sge::audio::pool &
sanguis::client::machine::sound_pool()
{
	return sound_pool_;
}

sge::font::object &
sanguis::client::machine::font()
{
	return font_;
}

bool sanguis::client::machine::key_pressed(
	sge::input::key_code const key) const
{
	return ks[key];
}

sanguis::client::console_wrapper &
sanguis::client::machine::con_wrapper()
{
	return con_wrapper_;
}

sanguis::load::context const &
sanguis::client::machine::resources() const
{
	return resources_;
}
