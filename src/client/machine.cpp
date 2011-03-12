#include "machine.hpp"
#include "events/message.hpp"
#include "cursor/object.hpp"
#include "events/tick.hpp"
#include "../net/exception.hpp"
#include "../messages/connect.hpp"
#include "../messages/disconnect.hpp"
#include "../messages/create.hpp"
#include "../messages/base.hpp"
#include "../messages/net_error.hpp"
#include "../net/deserialize.hpp"
#include "../net/serialize.hpp"
#include "../log.hpp"

#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/console/gfx.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/device.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/systems/instance.hpp>

#include <fcppt/algorithm/append.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/math/compare.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::client::machine::machine(
	config::settings::object &_settings,
	server_callback const &_server_callback,
	load::context const &_resources,
	sge::audio::pool &_sound_pool,
	sge::font::metrics_ptr const _font_metrics,
	sge::font::text::drawer &_font_drawer,
	sge::console::gfx &_console_gfx,
	sge::input::keyboard::device_ptr const _keyboard,
	sge::input::cursor::object_ptr const _cursor,
	sge::renderer::device_ptr const _renderer,
	sge::image2d::multi_loader &_image_loader,
	sge::audio::player_ptr const _audio_player,
	awl::mainloop::io_service_ptr const _io_service
)
:
	settings_(_settings),
	resources_(_resources),
	keyboard_(_keyboard),
	renderer_(_renderer),
	image_loader_(_image_loader),
	audio_player_(_audio_player),
	net_(
		_io_service
	),
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
	font_metrics_(_font_metrics),
	font_drawer_(_font_drawer),
	console_gfx_(_console_gfx),
	console_(
		_console_gfx,
		keyboard_,
		sge::input::keyboard::key_code::f1,
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
		keyboard_
	),
	cursor_(
		_cursor
	)
{
}

sanguis::client::machine::~machine()
{
}

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
		events::message(
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
		events::message(
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
		events::message(
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
	events::tick const &_event
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

		process_event(
			_event
		);

		if (console_gfx_.active())
			console_gfx_.draw();
	}

	screenshot_.process();

	return running_;
}
catch (net::exception const &e)
{
	process_event(
		events::message(
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

sanguis::client::config::settings::object &
sanguis::client::machine::settings()
{
	return settings_;
}

sge::renderer::device_ptr const
sanguis::client::machine::renderer() const
{
	return renderer_;
}

sge::image2d::multi_loader &
sanguis::client::machine::image_loader() const
{
	return image_loader_;
}

sge::input::keyboard::device_ptr const
sanguis::client::machine::keyboard() const
{
	return keyboard_;
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

sge::font::metrics_ptr const
sanguis::client::machine::font_metrics() const
{
	return font_metrics_;
}

sge::font::text::drawer &
sanguis::client::machine::font_drawer() const
{
	return font_drawer_;
}

sanguis::client::console &
sanguis::client::machine::console()
{
	return console_;
}

sanguis::load::context const &
sanguis::client::machine::resources() const
{
	return resources_;
}

sanguis::client::cursor::object & 
sanguis::client::machine::cursor()
{
	return cursor_;
}

sanguis::client::cursor::object const &
sanguis::client::machine::cursor() const
{
	return cursor_;
}
