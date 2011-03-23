#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ABS_ANGLE_TO_REL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ABS_ANGLE_TO_REL_HPP_INCLUDED

#include "is_rel_angle.hpp"
#include <fcppt/math/mod.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/math/twopi.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

/// Transform an arbitrary angle into the range [-pi,pi]
/**
 * @tparam T The type must be a floating point type
*/
template<
	typename T
>
typename boost::enable_if<
	boost::is_floating_point<
		T
	>,
	T
>::type
abs_angle_to_rel(
	T _angle
)
{
	_angle =
		fcppt::math::mod(
			_angle,
			fcppt::math::twopi<T>()
		);

	if(
		model::is_rel_angle(
			_angle
		)
	)
		return _angle;

	return
		_angle > 0
		?
			_angle - fcppt::math::pi<T>()
		:
			_angle + fcppt::math::pi<T>();
}

}
}
}
}
}

#endif
