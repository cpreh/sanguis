#include <sanguis/collision/both_intersections.hpp>
#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/intersection_pair.hpp>
#include <sanguis/collision/pos.hpp>
#include <sanguis/collision/rect.hpp>
#include <sanguis/collision/rect_ray_intersection.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::collision::intersection_pair const
sanguis::collision::both_intersections(
	sanguis::creator::pos const _pos,
	sanguis::collision::dir const _dir,
	sanguis::collision::pos const _tangent1,
	sanguis::collision::pos const _tangent2
)
{
	sanguis::collision::rect const rect(
		fcppt::math::vector::structure_cast<
			sanguis::collision::rect::vector
		>(
			_pos
			*
			sanguis::creator::tile_size::value
		),
		fcppt::math::dim::fill<
			sanguis::collision::rect::dim::dim_wrapper::value
		>(
			static_cast<
				sanguis::collision::unit
			>(
				sanguis::creator::tile_size::value
			)
		)
	);

	return
		sanguis::collision::intersection_pair(
			sanguis::collision::rect_ray_intersection(
				rect,
				_tangent1,
				_dir
			),
			sanguis::collision::rect_ray_intersection(
				rect,
				_tangent2,
				_dir
			)
		);
}
