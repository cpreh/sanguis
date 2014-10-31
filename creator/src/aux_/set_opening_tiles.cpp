#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/aux_/set_opening_tiles.hpp>
#include <fcppt/make_enum_range.hpp>


void
sanguis::creator::aux_::set_opening_tiles(
	sanguis::creator::grid &_grid,
	sanguis::creator::opening_container_array const &_openings
)
{
	for(
		auto const opening_type
		:
		fcppt::make_enum_range<
			sanguis::creator::opening_type
		>()
	)
		for(
			auto const &opening
			:
			_openings[
				opening_type
			]
		)
			_grid[
				opening.get()
			]
			=
			// TODO: Different tiles for entry/exit?
			sanguis::creator::tile::stairs;
}
