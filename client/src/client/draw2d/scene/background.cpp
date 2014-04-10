#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/background.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/background_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/client/object.hpp>
#include <sanguis/client/draw2d/sprite/client/parameters.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp>
#include <sanguis/client/load/context.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::background::background(
	sanguis::client::load::context const &_load_context,
	sanguis::client::draw2d::sprite::client::system &_client_system,
	sge::viewport::manager &_viewport_manager
)
:
	client_system_(
		_client_system
	),
	texture_(
		_load_context.resources().textures().load(
			sanguis::client::load::resource::texture_identifier(
				FCPPT_TEXT("background")
			)
		)
	),
	sprite_(
		sanguis::client::draw2d::sprite::client::parameters()
		.connection(
			client_system_.connection(
				sanguis::client::draw2d::z_ordering::background
			)
		)
		.pos(
			sanguis::client::draw2d::sprite::point::null()
		)
		.size(
			fcppt::math::dim::structure_cast<
				sanguis::client::draw2d::sprite::dim
			>(
				sanguis::client::draw2d::scene::background_dim(
					client_system_.renderer()
				)
			)
		)
		.texture(
			texture_
		)
		.texture_coordinates(
			sanguis::client::draw2d::scene::background_texture_coordinates(
				sanguis::client::draw2d::translation(
					sanguis::client::draw2d::translation::value_type::null()
				),
				client_system_.renderer(),
				*texture_
			)
		)
	),
	viewport_connection_(
		_viewport_manager.manage_callback(
			std::bind(
				&sanguis::client::draw2d::scene::background::reset_viewport,
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
	sanguis::client::draw2d::translation const _translation
)
{
	sprite_.texture_coordinates(
		sanguis::client::draw2d::scene::background_texture_coordinates(
			_translation,
			client_system_.renderer(),
			*texture_
		)
	);

	client_system_.render(
		_render_context,
		sanguis::client::draw2d::z_ordering::background
	);
}

void
sanguis::client::draw2d::scene::background::reset_viewport()
{
	sprite_.size(
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::sprite::dim
		>(
			sanguis::client::draw2d::scene::background_dim(
				client_system_.renderer()
			)
		)
	);
}
