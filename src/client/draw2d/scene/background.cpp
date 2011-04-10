#include "background.hpp"
#include "background_dim.hpp"
#include "background_texture_coordinates.hpp"
#include "../sprite/client/parameters.hpp"
#include "../sprite/dim.hpp"
#include "../sprite/point.hpp"
#include "../z_ordering.hpp"
#include "../../../load/context.hpp"
#include "../../../load/resource/context.hpp"
#include "../../../load/resource/textures.hpp"
#include "../../../load/resource/texture_identifier.hpp"
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::scene::background::background(
	load::context const &_load_context,
	sprite::client::system &_client_system,
	sge::viewport::manager &_viewport_manager
)
:
	client_system_(_client_system),
	texture_(
		_load_context.resources().textures().load(
			load::resource::texture_identifier(
				FCPPT_TEXT("background")
			)
		)
	),
	sprite_(
		draw2d::sprite::client::parameters()
		.system(
			&client_system_
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
		.order(
			draw2d::z_ordering::background
		)
		.texture_coordinates(
			scene::background_texture_coordinates(
				draw2d::vector2::null(),
				client_system_.renderer(),
				texture_
			)
		)
		.visible(
			true
		)
		.elements()
	),
	viewport_connection_(
		_viewport_manager.manage_callback(
			std::tr1::bind(
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
	draw2d::vector2 const &_translation
)
{
	sprite_.texture_coordinates(
		scene::background_texture_coordinates(
			_translation,
			client_system_.renderer(),
			texture_
		)
	);

	client_system_.render_advanced(
		draw2d::z_ordering::background,
		sge::sprite::default_equal()
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
