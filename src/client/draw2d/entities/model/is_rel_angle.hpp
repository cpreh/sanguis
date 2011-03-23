//          Copyright Carl Philipp Reh 2009 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_IS_REL_ANGLE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_IS_REL_ANGLE_HPP_INCLUDED

#include <fcppt/math/pi.hpp>
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

/// Checks if @a a is in [-pi,pi]
/**
 * @tparam T must be a floating point type
*/
template<
	typename T
>
typename boost::enable_if<
	boost::is_floating_point<
		T
	>,
	bool
>::type
is_rel_angle(
	T const _angle
)
{
	return
		_angle >= -fcppt::math::pi<T>()
		&& _angle <= fcppt::math::pi<T>();
}

}
}
}
}
}

#endif
