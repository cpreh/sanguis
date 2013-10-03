#ifndef SANGUIS_CREATOR_AUX__FIND_CLOSEST_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__FIND_CLOSEST_HPP_INCLUDED

#include <fcppt/optional.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace creator
{
namespace aux_
{

template<
	typename Attribute
>
fcppt::optional<
	sanguis::creator::pos
>
find_closest(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _pos,
	Attribute _attribute,
	sanguis::creator::pos::value_type _max_radius
)
{
	typedef
	fcppt::optional
	<
		sanguis::creator::pos
	>
	result_type;

	_max_radius =
		std::min(
			_max_radius,
			std::max(
				_grid.size().w() / 2,
				_grid.size().h() / 2
			)
		);

	unsigned leg = 0;
	unsigned radius = 1;
	unsigned steps = 0;
	auto x = _pos.x() + 1;
	auto y = _pos.y();

	while(
		radius
		<=
		_max_radius
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

		const
		sanguis::creator::pos
		pos(
			x,
			y
		);

		if(
			!
			fcppt::container::grid::in_range(
				_grid,
				pos
			)
		)
			continue;

		if(
			_attribute(
				_grid
				[
					pos
				]
			)
		)
		{
			return
				result_type(
					pos
				);
		}
	}
	
	// nothing was found, return empty optional
	return
		result_type();
}

}
}
}

#endif
