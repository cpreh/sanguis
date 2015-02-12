#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/light_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/client/texture_coordinates.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::sprite::client::texture_coordinates const
sanguis::client::draw2d::scene::light_texture_coordinates(
	sge::renderer::device::core &_renderer,
	sge::texture::part const &_texture
)
{
	sge::renderer::screen_size const background{
		sanguis::client::draw2d::scene::background_dim(
			_renderer
		)
	};

	sge::renderer::dim2 const texture_dim{
		_texture.size()
	};

	sanguis::client::draw2d::sprite::client::texture_coordinates::value_type const coordinates{
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::sprite::client::texture_coordinates::value_type,
			fcppt::cast::int_to_float_fun
		>(
			fcppt::math::dim::to_vector(
				background
			)
		)
		/
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::sprite::client::texture_coordinates::value_type,
			fcppt::cast::int_to_float_fun
		>(
			fcppt::math::dim::to_vector(
				texture_dim
			)
		)
	};

	return
		sanguis::client::draw2d::sprite::client::texture_coordinates{
			-coordinates,
			+coordinates
			+
			fcppt::math::vector::fill<
				sanguis::client::draw2d::sprite::client::texture_coordinates::value_type
			>(
				1.f
			)
		};
}