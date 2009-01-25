#ifndef SANGUIS_MESSAGES_TYPES_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_HPP_INCLUDED

#include <sge/math/vector/static.hpp>
#include <sge/math/dim/static.hpp>
#include <sge/math/circle.hpp>
#include <sge/string.hpp>
#include <boost/cstdint.hpp>
#include <string>

namespace sanguis
{
namespace messages
{

typedef float space_unit;
typedef sge::math::vector::static_<space_unit,2u>::type vector2;
typedef sge::math::vector::static_<space_unit,3u>::type vector3;
typedef sge::math::vector::static_<boost::int32_t,2u>::type ivector2_32;
typedef sge::math::vector::static_<boost::int32_t,3u>::type ivector3_32;
typedef sge::math::dim::static_<boost::int32_t,2u>::type idim2_32;
typedef std::wstring string; // FIXME
typedef vector2 pos_type;
typedef sge::math::dim::static_<space_unit,2u>::type dim_type;
typedef sge::math::circle<space_unit> circle_type;
typedef boost::uint32_t size_type;
typedef space_unit health_type;
typedef boost::uint32_t exp_type;
typedef boost::uint32_t level_type;

string host_to_net(const sge::string &s);
sge::string net_to_host(const string &s);

template<typename T>
messages::space_unit mu(const T &t)
{
	return static_cast<messages::space_unit>(t);
}

}
}

#define MESSAGE_TEXT(a) L ## a // FIXME

#endif
