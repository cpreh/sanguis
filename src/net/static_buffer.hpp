#ifndef SANGUIS_NET_STATIC_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_STATIC_BUFFER_HPP_INCLUDED

#include "value_type.hpp"
#include <boost/array.hpp>

namespace sanguis
{
namespace net
{

// TODO: asio doesn't work well other array types
typedef boost::array<
	value_type,
	4096
> static_buffer;

}
}

#endif
