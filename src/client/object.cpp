#include <sanguis/client/object.hpp>
#include <sanguis/client/config/settings/file.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/args/multi_sampling.hpp>
#include <sanguis/args/sge_options.hpp>
#include <sanguis/server/object.hpp>
#include <sanguis/duration.hpp>
#include <sge/config/media_path.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/system.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/systems/instance.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/window/instance.hpp>
#include <awl/mainloop/io_service.hpp>
#include <awl/mainloop/dispatcher.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/fatal.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>

sanguis::client::object::object(
	boost::program_options::variables_map const &_variables_map
)
:
	settings_(
		client::config::settings::file()
	),
	saver_(
		settings_
	),
	sys_(
		args::sge_options(
			_variables_map
		)
	),
	font_metrics_(
		sys_.font_system().create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			static_cast<sge::font::size_type>(15)
		)
	),
	font_drawer_(
		sys_.renderer(),
		sge::image::colors::white()
	),
	console_(
		FCPPT_TEXT('/')
	),
	console_gfx_(
		console_,
		sys_.renderer(),
		*font_metrics_,
		sys_.image_loader(),
		sys_.keyboard_collector(),
		sys_.viewport_manager(),
		_variables_map[
			"history-size"
		].as<
			sge::console::output_line_limit
		>()
	),
	window_(
		sys_.window()
	),
	io_service_(
		sys_.window().awl_io_service()
	),
	resources_(
		sys_.image_loader(),
		sys_.renderer(),
		sys_.audio_loader(),
		sys_.audio_player()
	),
	cursor_(
		sys_.cursor_demuxer()
	),
	gui_(
		sys_.renderer(),
		sys_.image_loader(),
		sys_.charconv_system(),
		sys_.viewport_manager(),
		sys_.keyboard_collector(),
		cursor_
	),
	machine_(
		settings_,
		gui_,
		std::tr1::bind(
			&object::create_server,
			this,
			std::tr1::placeholders::_1
		),
		resources_,
		*font_metrics_,
		font_drawer_,
		console_gfx_.get(),
		sys_.keyboard_collector(),
		cursor_,
		sys_.renderer(),
		sys_.image_loader(),
		sys_.audio_player(),
		*io_service_,
		sys_.viewport_manager()
	),
	frame_timer_(
		sanguis::timer::parameters(
			fcppt::chrono::seconds(
				1
			)
		)
	),
	server_(),
	scoped_machine_(
		machine_
	)
{
	if(
		args::multi_sampling(
			_variables_map
		).get()
		> 0
	)
		sys_.renderer().state(
			sge::renderer::state::list
			(
				sge::renderer::state::bool_::enable_multi_sampling = true
			)
		);
}

sanguis::client::object::~object()
{
}

int
sanguis::client::object::run()
{
	try
	{
		this->register_handler();

		io_service_->run();
	}
	catch(
		fcppt::exception const &_exception
	)
	{
		FCPPT_LOG_FATAL(
			client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Client error: ")
				<< _exception.string()
		);

		this->quit_server();

		return EXIT_FAILURE;
	}

	return this->quit_server();
}

void
sanguis::client::object::register_handler()
{
	io_service_->post(
		std::tr1::bind(
			&object::loop_handler,
			this
		)
	);
}

void
sanguis::client::object::loop_handler()
{
	if(
		!machine_.process(
			sge::timer::elapsed_and_reset<
				sanguis::duration
			>(
				frame_timer_
			)
		)
		||
		(
			server_
			&& !server_->running()
		)
	)
	{
		window_.awl_dispatcher()->stop();

		io_service_->stop();

		return;
	}

	machine_.draw();

	this->register_handler();
}

void
sanguis::client::object::create_server(
	net::port const _port
)
{
	if(
		server_
	)
	{
		this->quit_server();

		server_.reset();
	}

	server_.take(
		fcppt::make_unique_ptr<
			server::object
		>(
			_port,
			fcppt::cref(
				resources_
			)
		)
	);
}

int
sanguis::client::object::quit_server()
{
	if(
		server_
	)
		server_->quit();

	return
		server_
		?
			server_->run()
		:
			EXIT_SUCCESS;
}
