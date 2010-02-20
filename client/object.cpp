#include "object.hpp"

sanguis::client::object::object(
	sge::systems::instance &sys
)
:
	key_state_tracker_(
		sys.input_system()
	),
	font_metrics_(
		sys.font_system()->create_font(
			sge::config::media_path()
			/ FCPPT_TEXT("fonts")
			/ FCPPT_TEXT("default.ttf"),
			static_cast<sge::font::size_type>(15)
		)
	),
	font_drawer_(
		fcppt::make_shared_ptr<sge::font::drawer_3d>(
			sys.renderer(),
			sge::image::colors::white()
		)
	),
	font_(
		metrics,
		drawer
	),
	texture_manager_(
		sys.renderer(),
		sge::texture::default_creator<sge::texture::no_fragmented>(
			sys.renderer(),
			sge::image::color::format::rgba8, // TODO: what do we want to use here?
			sge::renderer::filter::linear
		)
	),
	console_(
		FCPPT_TEXT('/')
	),
	console_gfx_(
		console_,
		sys.renderer(),
		sge::image::colors::white(),
		font_metrics_,
		sys.input_system(),
		sge::console::sprite_object(
			sge::console::sprite_parameters()
			.texture(
				sge::texture::add_image(
					texman,
					sys.image_loader()->load(
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
					sys.renderer()->screen_size().w(),
					static_cast<
						sge::console::sprite_object::unit
					>(
						sys.renderer()->screen_size().h() / 2
					)
				)
			)
			.elements()
		),
		vm["history-size"].as<sge::console::gfx::output_line_limit>()
	),
	audio_loader_(
		sys.plugin_manager()
	),
	sound_pool_(),
	machine_(
		resources,
		sys,
		sound_pool_,
		font_,
		ks_,
		console_gfx_
	)
{
	if(vm.count("multi_sampling"))
		sys.renderer()->state(
			sge::renderer::state::list
			(
				sge::renderer::state::bool_::enable_multi_sampling = true
			)
		);

	machine_.initiate();
}
