#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/set_opening_tiles.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/enum/make_range.hpp>


void
sanguis::creator::impl::set_opening_tiles(
	sanguis::creator::grid &_grid,
	sanguis::creator::opening_container_array const &_openings
)
{
	for(
		auto const opening_type
		:
		fcppt::enum_::make_range<
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
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::grid::at_optional(
					_grid,
					opening.get()
				)
			).get() =
				// TODO: Different tiles for entry/exit?
				sanguis::creator::tile::stairs;
}
