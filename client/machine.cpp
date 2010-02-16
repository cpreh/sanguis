#include "machine.hpp"
#include "message_event.hpp"
#include "cursor/object.hpp"
#include "../net/exception.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/create.hpp"
#include "../messages/base.hpp"
#include "../messages/net_error.hpp"
#include "../serialization.hpp"
#include "../log.hpp"
#include "../media_path.hpp"
#include "../resolution.hpp"
#include "../tick_event.hpp"
#include <sge/systems/instance.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/math/compare.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::client::machine::machine(
	server_callback const &_server_callback,
	load::context const &_resources,
	sge::systems::instance &_sys,
	sge::audio::pool &_sound_pool,
	sge::font::object &_font,
	sge::input::key_state_tracker &_ks,
	sge::console::gfx &_console)
:
	resources_(_resources),
	s_conn(
		net_.register_connect(
			std::tr1::bind(
				&machine::connect_callback,
				this
			)
		)
	),
	s_disconn(
		net_.register_disconnect(
			std::tr1::bind(
				&machine::disconnect_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	s_data(
		net_.register_data(
			std::tr1::bind(
				&machine::data_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	sys_(_sys),
	sound_pool_(_sound_pool),
	font_(_font),
	ks(_ks),
	console(_console),
	console_stdlib(
		_console.object(),
		std::tr1::bind(
			&sge::console::gfx::print_line,
			&_console,
			std::tr1::placeholders::_1
		),
		std::tr1::bind(
			&sge::console::gfx::print_line,
			&_console,
			std::tr1::placeholders::_1
		)
	),
	console_wrapper_(
		_console,
		sys_.input_system(),
		sge::input::kc::key_f1
	),
	running_(true),
	server_callback_(_server_callback),
	screenshot_(
		sys_.renderer(),
		sys_.image_loader(),
		sys_.input_system()
	),
	cursor_(
		new sanguis::client::cursor::object(
			sys_.image_loader(),
			sys_.renderer()
		)
	),
	gameover_names_(),
	gameover_score_()
{}

void sanguis::client::machine::start_server()
{
	server_callback_(1337); // FIXME
}

void
sanguis::client::machine::connect(
	net::hostname_type const &hostname,
	net::port_type const port)
{
	net_.connect(
		hostname,
		port
	);
}

void sanguis::client::machine::cancel_connect()
{
	net_.disconnect();
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
	fcppt::string const &)
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
	fcppt::algorithm::append(
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

sanguis::net::client &
sanguis::client::machine::net()
{
	return net_;
}

bool sanguis::client::machine::process(
	tick_event const &t
)
try
{
	if (out_buffer.size())
	{
		net_.queue(out_buffer);
		out_buffer.clear();
	}

	net_.process();

	{
	sge::renderer::scoped_block const block_(
		sys_.renderer());

	process_event(t);

	if (console.active())
		console.draw();

	if (ks[sge::input::kc::key_escape])
		quit();
	}

	screenshot_.process();

	return running_;
}
catch (net::exception const &e)
{
	process_event(
		message_event(
			messages::create(
				messages::net_error(
					fcppt::utf8::convert(
						e.string()
					)
				)
			)
		)
	);
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

bool
sanguis::client::machine::key_pressed(
	sge::input::key_code const key
) const
{
	return ks[key];
}

sanguis::client::console &
sanguis::client::machine::console_wrapper()
{
	return console_wrapper_;
}

sanguis::load::context const &
sanguis::client::machine::resources() const
{
	return resources_;
}

sanguis::client::cursor::object_ptr const 
sanguis::client::machine::cursor()
{
	return cursor_;
}

sanguis::client::cursor::const_object_ptr const 
sanguis::client::machine::cursor() const
{
	return cursor_;
}

sanguis::client::highscore::name_container const &
sanguis::client::machine::gameover_names() const
{
	return gameover_names_;
}

sanguis::client::highscore::name_container &
sanguis::client::machine::gameover_names()
{
	return gameover_names_;
}

sanguis::client::highscore::score_type
sanguis::client::machine::gameover_score()
{
	return gameover_score_;
}

void
sanguis::client::machine::gameover_score(
	client::highscore::score_type const _gameover_score
)
{
	gameover_score_ = _gameover_score;
}
