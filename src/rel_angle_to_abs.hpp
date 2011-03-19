#ifndef SANGUIS_REL_ANGLE_TO_ABS_HPP_INCLUDED
#define SANGUIS_REL_ANGLE_TO_ABS_HPP_INCLUDED

#include "exception.hpp"
#include <fcppt/math/is_rel_angle.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace sanguis
{

// TODO: replace by fcppt::math:: stuff?
template<
	typename T
>
typename boost::enable_if<
	boost::is_floating_point<
		T
	>,
	T
>::type
rel_angle_to_abs(
	T const _angle
)
{
	if(
		!fcppt::math::is_rel_angle(
			_angle
		)
	)
		throw sanguis::exception(
			(
				fcppt::format(
					FCPPT_TEXT("math::rel_angle_to_abs: relative angle %1% out of range!")
				)
				% _angle
			).str()
		);

	if(
		fcppt::math::almost_zero(
			_angle
		)
	)
		return static_cast<T>(0);

	return
		_angle > static_cast<T>(0)
		?
			_angle
		:
			fcppt::math::twopi<T>()
			+
			_angle;
}

}

#endif
