#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/closest_empty.hpp>
#include <sanguis/creator/impl/find_closest.hpp>
#include <sanguis/creator/impl/optional_pos.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::creator::impl::optional_pos
sanguis::creator::impl::closest_empty(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _pos
)
{
	return
		sanguis::creator::impl::find_closest(
			_grid,
			_pos,
			[&_grid](
				sanguis::creator::pos const _p
			){
				return
					_grid[_p]
					==
					sanguis::creator::tile::nothing;
			},
			fcppt::optional<
				sanguis::creator::pos::value_type
			>{}
		);
}
