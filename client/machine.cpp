#include "machine.hpp"
#include "make_screenshot_path.hpp"
#include "message_event.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/create.hpp"
#include "../messages/base.hpp"
#include "../serialization.hpp"
#include "../log.hpp"
#include <sge/math/compare.hpp>
#include <sge/systems/instance.hpp>
#include <sge/renderer/screenshot.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/algorithm/append.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/construct.hpp>

sanguis::client::machine::machine(
	load::context const &_resources,
	sge::systems::instance &_sys,
	sge::audio::pool &_sound_pool,
	sge::font::object &_font,
	sge::input::key_state_tracker &_ks,
	sge::console::gfx &_console,
	net::hostname_type const &_hostname,
	net::port_type const _port) 
:
	resources_(_resources),
	hostname_(_hostname),
	port_(_port),
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
	input_connection(
		_sys.input_system()->register_callback(
			boost::bind(
				&machine::input_callback,
				this,
				_1))),
	sys_(_sys),
	sound_pool_(_sound_pool),
	font_(_font),
	ks(_ks),
	console(_console),
	console_stdlib(
		_console.object(),
		boost::bind(
			&sge::console::gfx::print,
			&_console,
			_1),
		boost::bind(
			&sge::console::gfx::print,
			&_console,
			_1)),
	console_wrapper_(
		_console,
		sys_.input_system(),
		sge::input::kc::key_f1),
	running_(true),
	screenshot_(false)
{}

void sanguis::client::machine::connect()
{
	net_.connect(hostname_,port_);
}

void sanguis::client::machine::connect_callback()
{
	process_event(
		message_event(
			messages::create(
				messages::connect()
			)
		)
	);
}

void sanguis::client::machine::disconnect_callback(
	sge::string const &)
{
	process_event(
		message_event(
			messages::create(
				messages::disconnect()
			)
		)
	);
}

void sanguis::client::machine::process_message(
	messages::auto_ptr ptr)
{
	process_event(
		message_event(
			ptr
		)
	);
}

void sanguis::client::machine::data_callback(
	net::data_type const &data)
{
	sge::algorithm::append(
		in_buffer,
		data
	);
	//while (messages::auto_ptr p = deserialize(in_buffer))
	//	process_message(p);
	for(;;)
	{
		messages::auto_ptr p = deserialize(in_buffer);
		if(!p.get())
			return;
		process_message(p);
	}
}

void sanguis::client::machine::send(
	messages::auto_ptr m)
{
	serialize(
		m,
		out_buffer);
}

sanguis::net::hostname_type
sanguis::client::machine::hostname() const
{
	return hostname_;
}

sanguis::net::port_type
sanguis::client::machine::port() const
{
	return port_;
}

sanguis::net::client &
sanguis::client::machine::net()
{
	return net_;
}

void sanguis::client::machine::hostname(net::hostname_type const &_hostname)
{
	hostname_ = _hostname;
}

void sanguis::client::machine::port(net::port_type const _port)
{
	port_ = _port;
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

	{
	sge::renderer::scoped_block const block_(sys_.renderer());
	process_event(t);

	if (console.active())
		console.draw();

	if (ks[sge::input::kc::key_escape])
		quit();
	}

	if (screenshot_)
	{
		make_screenshot();
		screenshot_ = false;
	}

	return running_;
}

void sanguis::client::machine::quit()
{
	running_ = false;
}

void sanguis::client::machine::dispatch()
{
	sge::mainloop::dispatch();
}

sge::renderer::device_ptr const
sanguis::client::machine::renderer() const
{
	return sys_.renderer();
}

sge::systems::instance &
sanguis::client::machine::sys() const
{
	return sys_;
}

sge::audio::player_ptr const
sanguis::client::machine::audio_player() const
{
	return sys_.audio_player();
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
sanguis::client::machine::console_wrapper()
{
	return console_wrapper_;
}

sanguis::load::context const &
sanguis::client::machine::resources() const
{
	return resources_;
}

void sanguis::client::machine::input_callback(
	sge::input::key_pair const &k)
{
	if (sge::math::almost_zero(k.value()))
		return;

	if (k.key().code() != sge::input::kc::key_print)
		return;
	
	screenshot_ = true;
}

void sanguis::client::machine::make_screenshot()
{
	sge::filesystem::path const p = 
		make_screenshot_path();
	
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("writing screenshot: ")
		             << p);
	
	sge::renderer::screenshot(
		sys().renderer(),
		sys().image_loader(),
		p);
}
