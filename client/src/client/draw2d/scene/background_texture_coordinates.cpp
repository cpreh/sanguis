#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/background_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/client/texture_coordinates.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::sprite::client::texture_coordinates const
sanguis::client::draw2d::scene::background_texture_coordinates(
	sanguis::client::draw2d::translation const _translation,
	sge::renderer::device::core &_device,
	sge::texture::part const &_texture
)
{
	typedef sanguis::client::draw2d::sprite::client::texture_coordinates coordinates;

	typedef coordinates::value_type pos_type;

	pos_type const dim(
		fcppt::math::vector::structure_cast<
			pos_type,
			fcppt::cast::int_to_float_fun
		>(
			fcppt::math::dim::to_vector(
				sanguis::client::draw2d::scene::background_dim(
					_device
				)
			)
		)
	);

	coordinates const base(
		fcppt::math::vector::null<
			pos_type
		>(),
		dim
		/
		fcppt::math::vector::structure_cast<
			pos_type,
			fcppt::cast::int_to_float_fun
		>(
			fcppt::math::dim::to_vector(
				_texture.size()
			)
		)
	);

	pos_type const rel(
		fcppt::math::vector::structure_cast<
			pos_type,
			fcppt::cast::size_fun
		>(
			-_translation.get()
		)
		/
		dim
		*
		base.second
	);

	return
		coordinates(
			base.first + rel,
			base.second + rel
		);
}
