#include "object.hpp"
#include "message_event.hpp"
#include "states/menu.hpp"
#include "../args/multi_sampling.hpp"
#include "../server/object.hpp"
#include "../media_path.hpp"
#include "../tick_event.hpp"
#include "../time_type.hpp"

#include <sge/config/media_path.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/font/drawer_3d.hpp>
#include <sge/font/size_type.hpp>
#include <sge/font/system.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/loader.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/systems/instance.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>

#include <fcppt/function/object.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

#include <cstdlib>

sanguis::client::object::object(
	sge::systems::instance &sys_,
	boost::program_options::variables_map const &variables_map_
)
:
	sys_(sys_),
	key_state_tracker_(
		sys_.input_system()
	),
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
	font_(
		font_metrics_,
		font_drawer_
	),
	texture_manager_(
		sys_.renderer(),
		sge::texture::default_creator<
			sge::texture::no_fragmented
		>(
			sys_.renderer(),
			sge::image::color::format::rgba8, // TODO: what do we want to use here?
			sge::renderer::filter::linear
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
				sge::texture::add_image(
					texture_manager_,
					sys_.image_loader()->load(
						sanguis::media_path()
						/ FCPPT_TEXT("console_back.png")
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
		variables_map_[
			"history-size"
		].as<
			sge::console::output_line_limit
		>()
	),
	audio_loader_(
		sys_.plugin_manager()
	),
	sound_pool_(),
	resources_(
		sys_.image_loader(),
		sys_.renderer(),
		audio_loader_,
		sys_.audio_player(),
		sound_pool_
	),
	machine_(
		std::tr1::bind(
			&object::create_server,
			this,
			std::tr1::placeholders::_1
		),
		resources_,
		sound_pool_,
		font_,
		key_state_tracker_,
		console_gfx_,
		sys_.input_system(),
		sys_.renderer(),
		sys_.image_loader(),
		sys_.font_system(),
		sys_.audio_player()
	),
	server_(),
	variables_map_(variables_map_)
{
	if(	
		args::multi_sampling(
			variables_map_
		)
		> 0
	)
		sys_.renderer()->state(
			sge::renderer::state::list
			(
				sge::renderer::state::bool_::enable_multi_sampling = true
			)
		);

	machine_.initiate();
}

sanguis::client::object::~object()
{}

int
sanguis::client::object::run()
{
	sge::time::timer frame_timer(
		sge::time::second(1)
	);

	while(
		machine_.process(
			tick_event(
				static_cast<
					time_type
				>(
					frame_timer.reset()
				)
			)
		)
	) ;

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

void
sanguis::client::object::create_server(
	net::port_type const port_
)
{
	// HACK HACK, FIXME!
	static_cast<
		std::map<
			std::string,
			boost::program_options::variable_value
		> &
	>(
		variables_map_
	)[
		"serverport"
	] =
		boost::program_options::variable_value(
			boost::any(
				port_
			),
			false
		);

	server_.take(
		fcppt::make_auto_ptr<
			server::object
		>(
			sys_,
			variables_map_,
			resources_
		)
	);
}
