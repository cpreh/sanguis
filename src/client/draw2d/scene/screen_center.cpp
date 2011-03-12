#include "screen_center.hpp"
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sanguis::client::draw2d::vector2 const
sanguis::client::draw2d::scene::screen_center(
	sprite::point const &player_center_,
	sge::renderer::screen_size const &screen_size_
)
{
	sprite::point const translation_center(
		-player_center_
		+ fcppt::math::dim::structure_cast<
			fcppt::math::dim::static_<
				sprite::unit,
				2
			>::type
		>(
			screen_size_ / 2u
		)
	);

	return
		fcppt::math::vector::structure_cast<
			vector2
		>(
			translation_center
		);
}
