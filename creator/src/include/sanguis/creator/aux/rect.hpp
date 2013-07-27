#ifndef SANGUIS_CREATOR_AUX_RECT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_RECT_HPP_INCLUDED

#include <sanguis/creator/signed_pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cstdlib>
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
rect
(
	sanguis::creator::signed_pos const &_start,
	sanguis::creator::signed_pos const &_end,
	Callback const &_callback
)
{
	typedef
	sanguis::creator::signed_pos::value_type
	int_type;

	int_type x0 = static_cast<int_type>(_start[0]);
	int_type y0 = static_cast<int_type>(_start[1]);
	int_type x1 = static_cast<int_type>(_end[0]);
	int_type y1 = static_cast<int_type>(_end[1]);

	if (x0 > x1)
		std::swap(x0, x1);
	if (y0 > y1)
		std::swap(y0, y1);

	for (int_type y = y0; y < y1; ++y)
	{
		_callback(
			sanguis::creator::signed_pos(
				x0,
				y));
		_callback(
			sanguis::creator::signed_pos(
				x1,
				y));
	}

	for (int_type x = x0 + 1; x < x1 - 1; ++x)
	{
		_callback(
			sanguis::creator::signed_pos(
				x,
				y0));
		_callback(
			sanguis::creator::signed_pos(
				x,
				y1));
	}
}

}
}
}

#endif
