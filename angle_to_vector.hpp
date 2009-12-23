#ifndef SANGUIS_ANGLE_TO_VECTOR_HPP_INCLUDED
#define SANGUIS_ANGLE_TO_VECTOR_HPP_INCLUDED

#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <cmath>

namespace sanguis
{

template<
	typename T
>
typename boost::enable_if<
	boost::is_floating_point<T>,
	typename fcppt::math::vector::static_<T, 2>::type
>::type
angle_to_vector(
	T const angle
)
{
	return typename fcppt::math::vector::static_<
		T,
		2
	>::type(
		std::cos(angle),
		std::sin(angle));
}

}

#endif
