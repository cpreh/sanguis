#ifndef SANGUIS_ANGLE_VECTOR_HPP_INCLUDED
#define SANGUIS_ANGLE_VECTOR_HPP_INCLUDED

#include <sge/math/vector.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <cmath>

namespace sanguis
{

template<typename T>
typename boost::enable_if<
	boost::is_floating_point<T>,
	sge::math::vector<T, 2>
>::type
	angle_to_vector(T const angle)
{
	return sge::math::vector<T,2>(std::cos(angle),std::sin(angle));
}

}

#endif
