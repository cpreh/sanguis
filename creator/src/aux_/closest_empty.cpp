#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux_/closest_empty.hpp>
#include <sanguis/creator/aux_/find_closest.hpp>
#include <sanguis/creator/aux_/optional_pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::creator::aux_::optional_pos const
sanguis::creator::aux_::closest_empty(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _pos
)
{
	return
		sanguis::creator::aux_::find_closest(
			_grid,
			_pos,
			[](
				sanguis::creator::tile const _tile
			){
				return
					_tile
					==
					sanguis::creator::tile::nothing;
			},
			std::max(_grid.size().w(), _grid.size().h())
		);
}
