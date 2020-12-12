#ifndef SANGUIS_CREATOR_IMPL_RECT_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RECT_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>

namespace sanguis
{
namespace creator
{
namespace impl
{

template<
	typename Callback
>
void
rect(
	sanguis::creator::rect const &_rect,
	Callback const &_callback
)
{
	using
	int_type
	=
	sanguis::creator::pos::value_type;

	int_type x0 = _rect.left();
	int_type y0 = _rect.top();
	int_type x1 = _rect.right();
	int_type y1 = _rect.bottom();

	for (int_type y = y0; y < y1; ++y)
	{
		_callback(
			sanguis::creator::pos(
				x0,
				y));
		_callback(
			sanguis::creator::pos(
				x1 - 1,
				y));
	}

	for (int_type x = x0 + 1; x < x1; ++x)
	{
		_callback(
			sanguis::creator::pos(
				x,
				y0));
		_callback(
			sanguis::creator::pos(
				x,
				y1 - 1));
	}
}

}
}
}

#endif
