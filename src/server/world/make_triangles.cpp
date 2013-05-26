#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/world/convert_pos.hpp>
#include <sanguis/server/world/make_triangles.hpp>
#include <sge/projectile/triangle.hpp>
#include <sge/projectile/vector2.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <fcppt/container/grid/make_pos_crange.hpp>


sge::projectile::shape::triangle_sequence
sanguis::server::world::make_triangles(
	sanguis::creator::grid const &_tiles
)
{
	sge::projectile::shape::triangle_sequence result;

	for(
		auto const element
		:
		fcppt::container::grid::make_pos_crange(
			_tiles
		)
	)
	{
		if(
			!sanguis::creator::tile_is_solid(
				element.value()
			)
		)
			continue;

		sge::projectile::vector2 const top_left(
			sanguis::server::world::convert_pos(
				element.pos()
			)
		);

		sge::projectile::vector2 const top_right(
			sanguis::server::world::convert_pos(
				sanguis::creator::pos(
					element.pos().w() + 1,
					element.pos().h()
				)
			)
		);

		sge::projectile::vector2 const bottom_left(
			sanguis::server::world::convert_pos(
				sanguis::creator::pos(
					element.pos().w(),
					element.pos().h() + 1
				)
			)
		);

		sge::projectile::vector2 const bottom_right(
			sanguis::server::world::convert_pos(
				sanguis::creator::pos(
					element.pos().w() + 1,
					element.pos().h() + 1
				)
			)
		);

		result.push_back(
			sge::projectile::triangle{{
				top_left,
				top_right,
				bottom_left
			}}
		);

		result.push_back(
			sge::projectile::triangle{{
				bottom_left,
				top_right,
				bottom_right
			}}
		);
	}

	return
		result;
}
