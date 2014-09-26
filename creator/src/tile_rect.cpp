#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_rect.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::creator::rect const
sanguis::creator::tile_rect(
	sanguis::creator::tile const _tile
)
{
	FCPPT_ASSERT_PRE(
		sanguis::creator::tile_is_solid(
			_tile
		)
	);

	switch(
		_tile
	)
	{
	case sanguis::creator::tile::nothing:
		break;
	default:
		return
			sanguis::creator::rect(
				sanguis::creator::rect::vector::null(),
				fcppt::math::dim::fill<
					sanguis::creator::rect::dim
				>(
					sanguis::creator::tile_size::value
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
