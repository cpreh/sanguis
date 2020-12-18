#ifndef SANGUIS_CREATOR_IMPL_FIND_CLOSEST_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_FIND_CLOSEST_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/optional_pos.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/container/grid/object_fwd.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

template<
	typename Attribute,
	typename Value
>
sanguis::creator::impl::optional_pos
find_closest(
	fcppt::container::grid::object<
		Value,
		2U
	> const &_grid,
	sanguis::creator::pos const &_pos,
	Attribute const _attribute,
	fcppt::optional::object<
		sanguis::creator::pos::value_type
	> _max_radius
)
{
	auto const w = _grid.size().w();
	auto const h = _grid.size().h();
	auto const x0 = _pos.x();
	auto const y0 = _pos.y();

	auto const max_radius =
		fcppt::optional::from(
			_max_radius,
			[w,h,x0,y0]
			{
				return
				// at most we have to go the
				// manhattan distance to the farthest corner:
				std::max(
					{
					// top left or
					x0 + y0,
					// top right or
					w - x0 + y0,
					// bottom left or
					x0 + h - y0,
					// bottom right
					w - x0 + h - y0
					}
				);
			}
		);

	unsigned leg = 0;
	unsigned radius = 1;
	unsigned steps = 0;
	auto x = _pos.x() + 1;
	auto y = _pos.y();

	while(
		radius
		<=
		max_radius
	)
	{
		switch(
			leg
		)
		{
			case 0:
				x--;
				y--;
				break;
			case 1:
				x--;
				y++;
				break;
			case 2:
				x++;
				y++;
				break;
			case 3:
				x++;
				y--;
				break;
			default:
				break;
		}

		steps++;

		if(
			steps
			==
			radius
		)
		{
			leg++;
			steps = 0;
		}

		if(
			leg
			==
			4
		)
		{
			radius++;
			x++;
			leg = 0;
		}

		sanguis::creator::pos const pos{x, y};

		if(
			!
			fcppt::container::grid::in_range(
				_grid,
				pos
			)
		)
		{
			continue;
		}

		if(
			_attribute(
					pos
			)
		)
		{
			return
				sanguis::creator::impl::optional_pos(
					pos
				);
		}
	}

	// nothing was found, return empty optional
	return
		sanguis::creator::impl::optional_pos();
}

}
}
}

#endif
