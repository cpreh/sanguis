#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/background_texture_coordinates.hpp>
#include <sanguis/client/draw2d/sprite/client/texture_coordinates.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
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

	coordinates const base(
		pos_type::null(),
		fcppt::math::dim::structure_cast<
			pos_type
		>(
			sanguis::client::draw2d::scene::background_dim(
				_device
			)
		)
		/
		fcppt::math::dim::structure_cast<
			pos_type
		>(
			_texture.size()
		)
	);

	pos_type const rel(
		fcppt::math::vector::structure_cast<
			pos_type
		>(
			-_translation.get()
		)
		/
		fcppt::math::dim::structure_cast<
			pos_type
		>(
			sanguis::client::draw2d::scene::background_dim(
				_device
			)
		)
		* base.second
	);

	return
		coordinates(
			base.first + rel,
			base.second + rel
		);
}
