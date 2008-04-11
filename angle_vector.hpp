#ifndef ANGLE_VECTOR_HPP_INCLUDED
#define ANGLE_VECTOR_HPP_INCLUDED

#include <sge/math/vector.hpp>
#include <sge/su.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <cmath>

template<typename T>
typename boost::enable_if<
	boost::is_floating_point<T>,
	sge::math::basic_vector<T,2>
	>::type
	angle_to_vector(const T angle)
{
	return sge::math::basic_vector<T,2>(std::cos(angle),std::sin(angle));
}

#endif
