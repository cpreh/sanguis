#ifndef SANGUIS_CREATOR_IMPL_FILLED_RECT_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_FILLED_RECT_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>

namespace sanguis
{
namespace creator
{
namespace impl
{

template
<
	typename Callback
>
void
filled_rect
(
	sanguis::creator::rect const &_rect,
	Callback const &_callback
)
{
	typedef
	sanguis::creator::pos::value_type
	int_type;

	for (int_type y = _rect.top(); y < _rect.bottom(); ++y)
	{
		for (int_type x = _rect.left(); x < _rect.right(); ++x)
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

