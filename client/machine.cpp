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
#include <sge/math/compare.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/systems/instance.hpp>
#include <sge/audio/player.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/audio/pool.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/optional_impl.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/container/raw_vector_impl.hpp>
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
#include <sge/algorithm/append.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/utf8/convert.hpp>
#include <sge/fstream.hpp>
#include <boost/bind.hpp>

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
			boost::bind(
				&machine::connect_callback,
				this
			)
		)
	),
	s_disconn(
		net_.register_disconnect(
			boost::bind(
				&machine::disconnect_callback,
				this,
				_1
			)
		)
	),
	s_data(
		net_.register_data(
			boost::bind(
				&machine::data_callback,
				this,
				_1
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
		boost::bind(
			&sge::console::gfx::print,
			&_console,
			_1),
		boost::bind(
			&sge::console::gfx::print,
			&_console,
			_1
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
			sys_.renderer())),
	gameover_names_(),
	gameover_score_()
	/*
	ss_(sys_.renderer()),
	shader_(),
	shadervar_()
	target_(
		sys_.renderer()->create_texture(
			sge::math::dim::structure_cast<sge::renderer::texture::dim_type>(
				resolution()),
			sge::image::color::format::rgba8,
			sge::renderer::filter::linear,
			sge::renderer::resource_flags::none)),
	target_sprite_(
		sge::sprite::parameters()
			.texture(
				sge::texture::part_ptr(
					new sge::texture::part_raw(
						target_)))
			.depth(
				static_cast<sge::sprite::depth_type>(1)))
	*/
{
	/*
	sge::ifstream fragment_stream(
		media_path()/SGE_TEXT("shaders")/SGE_TEXT("fragment.glsl"));
	sge::ifstream vertex_stream(
		media_path()/SGE_TEXT("shaders")/SGE_TEXT("vertex.glsl"));

	shader_ = 
		sys_.renderer()->create_glsl_program(
			sge::renderer::glsl::istream_ref(
				vertex_stream),
			sge::renderer::glsl::istream_ref(
				fragment_stream));
	
	sys_.renderer()->glsl_program(
		shader_);

	shadervar_ = 
		shader_->uniform(SGE_TEXT("tex"));
	
	sge::renderer::glsl::uniform::single_value(
		shadervar_,
		static_cast<int>(0));
		*/
}

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
	/*
	{
	sys_.renderer()->glsl_program(
		sge::renderer::device::no_program);
	sge::renderer::scoped_block const block_(
		sys_.renderer());
	sge::renderer::scoped_target const t_(
		sys_.renderer(),
		target_);
	process_event(t);

	if (console.active())
		console.draw();

	if (ks[sge::input::kc::key_escape])
		quit();
	}

	sys_.renderer()->glsl_program(
		shader_);

	sge::renderer::scoped_block const block_(sys_.renderer());
	ss_.render(
		target_sprite_);
	*/

	screenshot_.process();

	return running_;
}
catch (net::exception const &e)
{
	process_event(
		message_event(
			messages::create(
				messages::net_error(
					sge::utf8::convert(
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

sanguis::client::highscore::name_container const &sanguis::client::machine::gameover_names() const
{
	return gameover_names_;
}

sanguis::client::highscore::name_container &sanguis::client::machine::gameover_names()
{
	return gameover_names_;
}

sanguis::client::highscore::score_type sanguis::client::machine::gameover_score()
{
	return gameover_score_;
}

void sanguis::client::machine::gameover_score(
	client::highscore::score_type const _gameover_score)
{
	gameover_score_ = _gameover_score;
}
