#include <sanguis/duration.hpp>
#include <sanguis/io_service_callback.hpp>
#include <sanguis/log_stream.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/client/create_systems.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/object.hpp>
#include <sanguis/client/object_base.hpp>
#include <sanguis/client/server.hpp>
#include <sanguis/client/server_callback.hpp>
#include <sanguis/client/systems.hpp>
#include <sanguis/client/args/history_size.hpp>
#include <sanguis/client/config/settings/file.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/gui/style/simple.hpp>
#include <sanguis/client/states/menu.hpp>
#include <alda/net/port.hpp>
#include <sge/audio/player.hpp>
#include <sge/config/media_path.hpp>
#include <sge/console/prefix.hpp>
#include <sge/font/added.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/system.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/desired_fps.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/timer/absolute_impl.hpp>
#include <sge/timer/difference_and_reset.hpp>
#include <sge/timer/scoped_frame_limiter.hpp>
#include <sge/window/system.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/fatal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <exception>
#include <functional>
#include <ostream>
#include <fcppt/config/external_end.hpp>


sanguis::client::object::object(
	boost::program_options::variables_map const &_variables_map
)
:
	sanguis::client::object_base(),
	settings_(
		client::config::settings::file()
	),
	saver_(
		settings_
	),
	io_service_(),
	sys_(
		sanguis::client::create_systems(
			_variables_map
		)
	),
	renderer_(
		sys_->renderer_device_core()
	),
	added_font_(
		sys_->font_system().add_font(
			sanguis::media_path()
			/
			FCPPT_TEXT("font")
			/
			FCPPT_TEXT("Electrolize-Regular.ttf")
		)
	),
	font_object_(
		sys_->font_system().create_font(
			sge::font::parameters()
			.family(
				FCPPT_TEXT("Electrolize")
			)
			.ttf_size(
				sge::font::ttf_size(
					20u
				)
			)
		)
	),
	resources_(
		sys_->image_system(),
		sys_->renderer_device_core(),
		sys_->audio_loader(),
		sys_->audio_player()
	),
	gui_style_(
		fcppt::unique_ptr_to_base<
			sge::gui::style::base
		>(
			fcppt::make_unique_ptr<
				sanguis::client::gui::style::simple
			>(
				resources_.resources().textures()
			)
		)
	),
	console_(
		sge::console::prefix(
			FCPPT_TEXT('/')
		)
	),
	console_gfx_(
		console_,
		sys_->renderer_device_ffp(),
		*font_object_,
		sys_->focus_collector(),
		sys_->viewport_manager(),
		sanguis::client::args::history_size(
			_variables_map
		),
		resources_.resources().textures()
	),
	cursor_{
		sys_->renderer_device_ffp(),
		sys_->cursor_demuxer(),
		resources_.resources().textures()
	},
	machine_(
		settings_,
		_variables_map,
		sanguis::client::server_callback{
			std::bind(
				&sanguis::client::object::create_server,
				this,
				std::placeholders::_1
			)
		},
		resources_,
		*gui_style_,
		sys_->window_system(),
		*font_object_,
		console_gfx_.get(),
		sys_->focus_collector(),
		sys_->cursor_demuxer(),
		sys_->renderer_system(),
		sys_->renderer_device_ffp(),
		sys_->renderer_device_index(),
		io_service_,
		sys_->viewport_manager(),
		cursor_
	),
	frame_timer_(),
	server_(),
	scoped_machine_(
		machine_
	)
{
}

sanguis::client::object::~object()
{
}

awl::main::exit_code
sanguis::client::object::run()
{
	this->register_handler();

	try
	{
		io_service_.run();
	}
	catch(
		fcppt::exception const &_exception
	)
	{
		FCPPT_LOG_FATAL(
			sanguis::client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Client error: ")
				<< _exception.string()
		);

		sys_->window_system().quit(
			awl::main::exit_failure()
		);
	}
	catch(
		std::exception const &_exception
	)
	{
		FCPPT_LOG_FATAL(
			sanguis::client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Client error: ")
				<< _exception.what()
		);

		sys_->window_system().quit(
			awl::main::exit_failure()
		);
	}

	awl::main::exit_code const server_ret(
		this->quit_server()
	);

	return
		server_ret
		==
		awl::main::exit_failure()
		?
			awl::main::exit_failure()
		:
			sys_->window_system().exit_code();
}

void
sanguis::client::object::register_handler()
{
	io_service_.post(
		sanguis::io_service_callback{
			std::bind(
				&sanguis::client::object::loop_handler,
				this
			)
		}
	);
}

void
sanguis::client::object::loop_handler()
{
	sge::timer::scoped_frame_limiter const limiter(
		sge::renderer::display_mode::desired_fps(
			renderer_.display_mode()
		)
	);

	fcppt::maybe_void(
		server_,
		[
			this
		](
			server_unique_ptr const &_server
		)
		{
			if(
				!_server->running()
			)
				sys_->window_system().quit(
					awl::main::exit_failure()
				);
		}
	);

	if(
		!machine_.process(
			sge::timer::difference_and_reset<
				sanguis::duration
			>(
				frame_timer_
			)
		)
	)
	{
		io_service_.stop();

		return;
	}

	machine_.draw();

	this->register_handler();
}

void
sanguis::client::object::create_server(
	alda::net::port const _port
)
{
	if(
		server_.has_value()
	)
	{
		this->quit_server();

		server_ =
			optional_server_unique_ptr();
	}
	else
		// The server and the client both do logging and this ensures
		// that it's thread-safe
		sanguis::log_stream().sync_with_stdio(
			true
		);

	server_ =
		optional_server_unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::server
			>(
				_port
			)
		);
}

awl::main::exit_code
sanguis::client::object::quit_server()
{
	fcppt::maybe_void(
		server_,
		[](
			server_unique_ptr const &_server
		)
		{
			_server->quit();
		}
	);

	return
		fcppt::maybe(
			server_,
			[]{
				return
					awl::main::exit_success();
			},
			[](
				server_unique_ptr const &_server
			)
			{
				return
					_server->run();
			}
		);
}
