#include "background_repetition.hpp"
#include "background_dim.hpp"
#include "../sprite/repetition.hpp"
#include <sge/texture/part.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::client::draw2d::vector2 const
sanguis::client::draw2d::scene::background_repetition(
	sge::renderer::device_ptr const _device,
	sge::texture::const_part_ptr const _texture
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::vector2
		>(
			fcppt::math::dim::structure_cast<
				draw2d::sprite::repetition
			>(
				scene::background_dim(
					_device
				)
			)
			/
			fcppt::math::dim::structure_cast<
				draw2d::sprite::repetition
			>(
				_texture->size()
			)
		);
}
