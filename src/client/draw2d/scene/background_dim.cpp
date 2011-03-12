#include "background_dim.hpp"
#include "../entities/simple_sprite.hpp"
#include <sge/texture/part.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/dynamic_cast.hpp>

sanguis::client::draw2d::dim2 const
sanguis::client::draw2d::scene::background_dim(
	entities::base const &_background
)
{
	return
		fcppt::math::dim::structure_cast<
			dim2
		>(
			fcppt::dynamic_cast_<
				entities::simple_sprite const &
			>(
				_background
			)
			.object()
			.texture()
			->area()
			.size()
		);
}
