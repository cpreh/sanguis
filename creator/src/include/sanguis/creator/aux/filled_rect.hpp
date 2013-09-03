#ifndef SANGUIS_CREATOR_AUX_FILLED_RECT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_FILLED_RECT_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace creator
{
namespace aux
{

template
<
	typename Callback
>
void
filled_rect
(
	sanguis::creator::pos const &_start,
	sanguis::creator::pos const &_end,
	Callback const &_callback
)
{
	typedef
	sanguis::creator::pos::value_type
	int_type;

	int_type x0 = _start[0];
	int_type y0 = _start[1];
	int_type x1 = _end[0];
	int_type y1 = _end[1];

	if (x0 > x1)
		std::swap(x0, x1);
	if (y0 > y1)
		std::swap(y0, y1);

	for (int_type y = y0; y < y1; ++y)
	{
		for (int_type x = x0; x < x1; ++x)
		{
			_callback(
				sanguis::creator::pos(
					x,
					y));
		}
	}
}

}
}
}

#endif
