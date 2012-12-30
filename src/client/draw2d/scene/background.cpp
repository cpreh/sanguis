#include <sanguis/client/draw2d/scene/background.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/background_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/client/parameters.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/load/context.hpp>
#include <sanguis/load/resource/context.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/resource/texture_identifier.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::background::background(
	sanguis::load::context const &_load_context,
	sanguis::client::draw2d::sprite::client::system &_client_system,
	sge::viewport::manager &_viewport_manager
)
:
	client_system_(
		_client_system
	),
	texture_(
		_load_context.resources().textures().load(
			load::resource::texture_identifier(
				FCPPT_TEXT("background")
			)
		)
	),
	sprite_(
		draw2d::sprite::client::parameters()
		.connection(
			client_system_.connection(
				draw2d::z_ordering::background
			)
		)
		.pos(
			draw2d::sprite::point::null()
		)
		.size(
			fcppt::math::dim::structure_cast<
				draw2d::sprite::dim
			>(
				scene::background_dim(
					client_system_.renderer()
				)
			)
		)
		.texture(
			texture_
		)
		.texture_coordinates(
			scene::background_texture_coordinates(
				draw2d::vector2::null(),
				client_system_.renderer(),
				*texture_
			)
		)
	),
	viewport_connection_(
		_viewport_manager.manage_callback(
			std::bind(
				&background::reset_viewport,
				this
			)
		)
	)
{
}

sanguis::client::draw2d::scene::background::~background()
{
}

void
sanguis::client::draw2d::scene::background::render(
	sge::renderer::context::core &_render_context,
	draw2d::vector2 const &_translation
)
{
	sprite_.texture_coordinates(
		scene::background_texture_coordinates(
			_translation,
			client_system_.renderer(),
			*texture_
		)
	);

	client_system_.render(
		_render_context,
		draw2d::z_ordering::background
	);
}

void
sanguis::client::draw2d::scene::background::reset_viewport()
{
	sprite_.size(
		fcppt::math::dim::structure_cast<
			draw2d::sprite::dim
		>(
			scene::background_dim(
				client_system_.renderer()
			)
		)
	);
}
