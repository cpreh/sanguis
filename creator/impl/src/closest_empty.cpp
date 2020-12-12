#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/closest_empty.hpp>
#include <sanguis/creator/impl/find_closest.hpp>
#include <sanguis/creator/impl/optional_pos.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/optional/object.hpp>


sanguis::creator::impl::optional_pos
sanguis::creator::impl::closest_empty(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const &_pos
)
{
	return
		sanguis::creator::impl::find_closest(
			_grid,
			_pos,
			[
				&_grid
			](
				sanguis::creator::pos const &_p
			){
				return
					FCPPT_ASSERT_OPTIONAL_ERROR(
						fcppt::container::grid::at_optional(
							_grid,
							_p
						)
					).get()
					==
					sanguis::creator::tile::nothing;
			},
			fcppt::optional::object<
				sanguis::creator::pos::value_type
			>{}
		);
}
