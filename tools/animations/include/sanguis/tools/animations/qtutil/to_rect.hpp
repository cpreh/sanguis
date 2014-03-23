#ifndef SANGUIS_TOOLS_ANIMATIONS_QTUTIL_TO_RECT_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_QTUTIL_TO_RECT_HPP_INCLUDED

#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QRect>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{
namespace qtutil
{

template<
	typename T
>
QRect
to_rect(
	fcppt::math::box::rect<
		T
	> const &_rect
)
{
	return
		QRect(
			static_cast<
				int
			>(
				_rect.left()
			),
			static_cast<
				int
			>(
				_rect.top()
			),
			static_cast<
				int
			>(
				_rect.w()
			),
			static_cast<
				int
			>(
				_rect.h()
			)
		);
}

}
}
}
}

#endif
