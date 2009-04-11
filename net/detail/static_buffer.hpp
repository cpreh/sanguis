#ifndef SANGUIS_NET_DETAIL_STATIC_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_STATIC_BUFFER_HPP_INCLUDED

#include <boost/array.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{

// TODO: asio doesn't work well with tr1::array
typedef boost::array<
	value_type,
	4096
> static_buffer;

}
}
}

#endif
