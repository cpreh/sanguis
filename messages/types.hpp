#ifndef SANGUIS_MESSAGES_TYPES_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_HPP_INCLUDED

#include <sge/math/vector.hpp>
#include <sge/math/dim.hpp>
#include <sge/string.hpp>
#include <boost/cstdint.hpp>
#include <string>

namespace sanguis
{
namespace messages
{
typedef float space_unit;
typedef sge::math::basic_vector<space_unit,2u> vector2;
typedef sge::math::basic_vector<space_unit,3u> vector3;
typedef sge::math::basic_vector<boost::int32_t,2u> ivector2_32;
typedef sge::math::basic_vector<boost::int32_t,3u> ivector3_32;
typedef sge::math::basic_dim<boost::int32_t,2u> idim2_32;
typedef std::wstring string;
typedef vector2 pos_type;
typedef sge::math::basic_dim<space_unit,2u> dim_type;
typedef boost::uint32_t size_type;
typedef space_unit health_type;
typedef boost::uint32_t exp_type;
typedef boost::uint32_t enum_type;

string host_to_net(const sge::string &s);
sge::string net_to_host(const string &s);

template<typename T>
messages::space_unit mu(const T &t)
{
	return static_cast<messages::space_unit>(t);
}

}
}

#define MESSAGE_TEXT(a) L ## a

#endif
