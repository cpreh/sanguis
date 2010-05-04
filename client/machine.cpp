#include "machine.hpp"
#include "message_event.hpp"
#include "cursor/object.hpp"
#include "../net/exception.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/create.hpp"
#include "../messages/base.hpp"
#include "../messages/net_error.hpp"
#include "../net/deserialize.hpp"
#include "../net/serialize.hpp"
#include "../log.hpp"
#include "../tick_event.hpp"

#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/console/gfx.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/input/system.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/systems/instance.hpp>

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
	sge::audio::pool &_sound_pool,
	sge::font::object &_font,
	sge::input::key_state_tracker &_ks,
	sge::console::gfx &_console,
	sge::input::system_ptr const input_system_,
	sge::renderer::device_ptr const renderer_,
	sge::image::loader_ptr const image_loader_,
	sge::font::system_ptr const font_system_,
	sge::audio::player_ptr const audio_player_
)
:
	resources_(_resources),
	input_system_(input_system_),
	renderer_(renderer_),
	image_loader_(image_loader_),
	font_system_(font_system_),
	audio_player_(audio_player_),
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
		input_system_,
		sge::input::kc::key_f1,
		std::tr1::bind(
			&machine::send,
			this,
			std::tr1::placeholders::_1
		)
	),
	running_(true),
	server_callback_(_server_callback),
	screenshot_(
		renderer_,
		image_loader_,
		input_system_
	),
	cursor_(
		new sanguis::client::cursor::object(
			image_loader_,
			renderer_
		)
	),
	gameover_names_(),
	gameover_score_()
{}

sanguis::client::machine::~machine()
{}

void
sanguis::client::machine::start_server()
{
	server_callback_(1337); // FIXME
}

void
sanguis::client::machine::connect(
	net::hostname_type const &hostname,
	net::port_type const port
)
{
	net_.connect(
		hostname,
		port
	);
}

void
sanguis::client::machine::cancel_connect()
{
	net_.disconnect();
}

void
sanguis::client::machine::connect_callback()
{
	process_event(
		message_event(
			messages::create(
				messages::connect()
			)
		)
	);
}

void
sanguis::client::machine::disconnect_callback(
	fcppt::string const &
)
{
	process_event(
		message_event(
			messages::create(
				messages::disconnect()
			)
		)
	);
}

void
sanguis::client::machine::process_message(
	messages::auto_ptr ptr
)
{
	process_event(
		message_event(
			ptr
		)
	);
}

void
sanguis::client::machine::data_callback(
	net::data_type const &data
)
{
	fcppt::algorithm::append(
		in_buffer,
		data
	);
	//while (messages::auto_ptr p = deserialize(in_buffer))
	//	process_message(p);
	for(;;)
	{
		messages::auto_ptr p = net::deserialize(in_buffer);
		if(!p.get())
			return;
		process_message(p);
	}
}

void
sanguis::client::machine::send(
	messages::auto_ptr m
)
{
	net::serialize(
		m,
		out_buffer
	);
}

sanguis::net::client &
sanguis::client::machine::net()
{
	return net_;
}

bool
sanguis::client::machine::process(
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
		renderer_
	);

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

void
sanguis::client::machine::quit()
{
	running_ = false;
}

void
sanguis::client::machine::dispatch()
{
	sge::mainloop::dispatch();
}

sge::renderer::device_ptr const
sanguis::client::machine::renderer() const
{
	return renderer_;
}

sge::image::loader_ptr const
sanguis::client::machine::image_loader() const
{
	return image_loader_;
}

sge::font::system_ptr const
sanguis::client::machine::font_system() const
{
	return font_system_;
}

sge::input::system_ptr const
sanguis::client::machine::input_system() const
{
	return input_system_;
}

sge::audio::player_ptr const
sanguis::client::machine::audio_player() const
{
	return audio_player_;
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
