#include "machine.hpp"
#include "events/connected.hpp"
#include "events/message.hpp"
#include "events/net_error.hpp"
#include "events/tick.hpp"
#include "log.hpp"
#include "../messages/auto_ptr.hpp"
#include "../messages/base.hpp"
#include "../net/deserialize.hpp"
#include "../net/serialize_to_circular_buffer.hpp"

#include <sge/console/gfx.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/systems/instance.hpp>

#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

sanguis::client::machine::machine(
	config::settings::object &_settings,
	client::gui::object &_gui,
	server_callback const &_server_callback,
	load::context const &_resources,
	sge::font::metrics_ptr const _font_metrics,
	sge::font::text::drawer &_font_drawer,
	sge::console::gfx &_console_gfx,
	sge::input::keyboard::device_ptr const _keyboard,
	client::cursor::object &_cursor,
	sge::renderer::device_ptr const _renderer,
	sge::image2d::multi_loader &_image_loader,
	sge::audio::player_ptr const _audio_player,
	awl::mainloop::io_service &_io_service,
	sge::viewport::manager &_viewport_manager
)
:
	settings_(_settings),
	gui_(_gui),
	resources_(_resources),
	keyboard_(_keyboard),
	renderer_(_renderer),
	image_loader_(_image_loader),
	audio_player_(_audio_player),
	viewport_manager_(_viewport_manager),
	net_(
		_io_service
	),
	s_conn_(
		net_.register_connect(
			std::tr1::bind(
				&machine::connect_callback,
				this
			)
		)
	),
	s_disconn_(
		net_.register_error(
			std::tr1::bind(
				&machine::error_callback,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	),
	s_data_(
		net_.register_data(
			std::tr1::bind(
				&machine::data_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	font_metrics_(_font_metrics),
	font_drawer_(_font_drawer),
	console_gfx_(_console_gfx),
	running_(true),
	server_callback_(_server_callback),
	cursor_(
		_cursor
	)
{
}

sanguis::client::machine::~machine()
{
}

void
sanguis::client::machine::quickstart(
	net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("machine::quickstart()"
		)
	);

	server_callback_(
		_port
	);

	this->connect(
		"localhost",
		_port
	);
}

void
sanguis::client::machine::connect(
	net::hostname const &_hostname,
	net::port const _port
)
{
	net_.connect(
		_hostname,
		_port
	);
}

void
sanguis::client::machine::disconnect()
{
	net_.disconnect();
}

void
sanguis::client::machine::send(
	messages::auto_ptr _message
)
{
	if(
		!net::serialize_to_circular_buffer(
			_message,
			net_.send_buffer()
		)
	)
	{
		FCPPT_LOG_ERROR(
			client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Not enough space left in the send_buffer")
		);
		// TODO:!
	}

	net_.queue_send();
}

bool
sanguis::client::machine::process(
	events::tick const &_event
)
{
	sge::renderer::scoped_block const block(
		renderer_
	);

	this->process_event(
		_event
	);

	return running_;
}

void
sanguis::client::machine::quit()
{
	FCPPT_LOG_DEBUG(
		client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Exiting the client!")
	);

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

sge::console::gfx &
sanguis::client::machine::console_gfx()
{
	return console_gfx_;
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

sanguis::client::gui::object &
sanguis::client::machine::gui() const
{
	return gui_;
}

sge::viewport::manager &
sanguis::client::machine::viewport_manager() const
{
	return viewport_manager_;
}

void
sanguis::client::machine::connect_callback()
{
	this->process_event(
		events::connected()
	);
}

void
sanguis::client::machine::error_callback(
	fcppt::string const &_message,
	boost::system::error_code const &_error
)
{
	this->process_event(
		events::net_error(
			_message,
			_error
		)
	);
}

void
sanguis::client::machine::data_callback(
	net::receive_buffer &_data
)
{
	for(;;)
	{
		messages::auto_ptr ret(
			net::deserialize(
				_data
			)
		);

		if(
			!ret.get()
		)
			return;

		this->process_event(
			events::message(
				ret
			)
		);
	}
}
