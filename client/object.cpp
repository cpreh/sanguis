#include "object.hpp"
#include "config/settings/file.hpp"
#include "events/message.hpp"
#include "states/menu.hpp"
#include "log.hpp"
#include "../args/multi_sampling.hpp"
#include "../server/object.hpp"
#include "../media_path.hpp"
#include "../tick_event.hpp"
#include "../time_type.hpp"
#include "../scoped_machine_impl.hpp"

#include <sge/config/media_path.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/font/drawer_3d.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/system.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/create_texture.hpp>
#include <sge/image/multi_loader.hpp>
#include <sge/mainloop/io_service.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/systems/instance.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/window/instance.hpp>

#include <fcppt/function/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/fatal.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

#include <cstdlib>

sanguis::client::object::object(
	sge::systems::instance &_sys,
	boost::program_options::variables_map const &_variables_map
)
:
	settings_(
		client::config::settings::file()
	),
	saver_(
		settings_
	),
	sys_(_sys),
	font_metrics_(
		sys_.font_system()->create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			static_cast<sge::font::size_type>(15)
		)
	),
	font_drawer_(
		fcppt::make_shared_ptr<
			sge::font::drawer_3d
		>(
			sys_.renderer(),
			sge::image::colors::white()
		)
	),
	console_(
		FCPPT_TEXT('/')
	),
	console_gfx_(
		console_,
		sys_.renderer(),
		sge::image::colors::white(),
		font_metrics_,
		sys_.input_system(),
		sge::console::sprite_object(
			sge::console::sprite_parameters()
			.texture(
				fcppt::make_shared_ptr<
					sge::texture::part_raw
				>(
					sge::image::create_texture(
						sanguis::media_path()
						/ FCPPT_TEXT("console_back.png"),
						sys_.renderer(),
						sys_.image_loader(),
						sge::renderer::filter::linear,
						sge::renderer::resource_flags::none
					)
				)
			)
			.pos(
				sge::console::sprite_object::point::null()
			)
			.size(
				sge::console::sprite_object::dim(
					sys_.renderer()->screen_size().w(),
					static_cast<
						sge::console::sprite_object::unit
					>(
						sys_.renderer()->screen_size().h() / 2
					)
				)
			)
			.elements()
		),
		_variables_map[
			"history-size"
		].as<
			sge::console::output_line_limit
		>()
	),
	sound_pool_(),
	io_service_(
		sys_.window()->io_service()
	),
	resources_(
		sys_.image_loader(),
		sys_.renderer(),
		sys_.audio_loader(),
		sys_.audio_player(),
		sound_pool_
	),
	machine_(
		settings_,
		std::tr1::bind(
			&object::create_server,
			this,
			std::tr1::placeholders::_1
		),
		resources_,
		sound_pool_,
		font_metrics_,
		font_drawer_,
		console_gfx_,
		sys_.input_system(),
		sys_.renderer(),
		sys_.image_loader(),
		sys_.audio_player(),
		io_service_
	),
	frame_timer_(
		sge::time::second(1)
	),
	server_(),
	running_(
		true
	),
	next_handler_(
		true
	),
	scoped_machine_(
		machine_
	)
{
	if(	
		args::multi_sampling(
			_variables_map
		)
		> 0
	)
		sys_.renderer()->state(
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
		while(
			running_
		)
		{
			if(
				next_handler_
			)
				register_handler();
		
			io_service_->run_one();
		}
	}
	catch(
		fcppt::exception const &e
	)
	{
		FCPPT_LOG_FATAL(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Client error: ")
				<< e.string()
		);

		quit_server();

		return EXIT_FAILURE;
	}

	return quit_server();
}

void
sanguis::client::object::register_handler()
{
	io_service_->dispatch(
		std::tr1::bind(
			&object::loop_handler,
			this
		)
	);

	next_handler_ = false;
}

void
sanguis::client::object::loop_handler()
{
	if(
		!machine_.process(
			tick_event(
				static_cast<
					time_type
				>(
					frame_timer_.reset()
				)
			)
		)
		||
		(
			server_
			&& !server_->running()
		)
	)
		running_ = false;

	next_handler_ = true;
}

void
sanguis::client::object::create_server(
	net::port_type const port_
)
{
	server_.take(
		fcppt::make_unique_ptr<
			server::object
		>(
			sys_,
			port_,
			resources_
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
