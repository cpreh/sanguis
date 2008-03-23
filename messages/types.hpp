#ifndef SANGUIS_MESSAGES_TYPES_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_HPP_INCLUDED

#include <sge/math/vector.hpp>
#include <sge/math/dim.hpp>
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

string host_to_net(const sge::string &s);
}
}

#ifdef SGE_NARROW_STRING
#define MESSAGE_TEXT(a) L ## a
#else
#define MESSAGE_TEXT(a) a
#endif


#endif
