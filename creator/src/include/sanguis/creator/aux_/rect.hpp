#ifndef SANGUIS_CREATOR_AUX__RECT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__RECT_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace creator
{
namespace aux_
{

template
<
	typename Callback
>
void
rect
(
	sanguis::creator::rect const &_rect,
	Callback const &_callback
)
{
	typedef
	sanguis::creator::pos::value_type
	int_type;

	auto p0 = _rect.pos();
	auto p1 = _rect.pos() + _rect.size();

	int_type x0 = p0.x();
	int_type y0 = p0.y();
	int_type x1 = p1.x();
	int_type y1 = p1.y();

	if (x0 > x1)
		std::swap(x0, x1);
	if (y0 > y1)
		std::swap(y0, y1);

	for (int_type y = y0; y < y1; ++y)
	{
		_callback(
			sanguis::creator::pos(
				x0,
				y));
		_callback(
			sanguis::creator::pos(
				x1,
				y));
	}

	for (int_type x = x0 + 1; x < x1 - 1; ++x)
	{
		_callback(
			sanguis::creator::pos(
				x,
				y0));
		_callback(
			sanguis::creator::pos(
				x,
				y1));
	}
}

}
}
}

#endif
