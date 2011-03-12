#ifndef SANGUIS_NET_DETAIL_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_CIRCULAR_BUFFER_HPP_INCLUDED

#include "../value_type.hpp"
#include <boost/circular_buffer.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{

typedef boost::circular_buffer<
	net::value_type
> circular_buffer;

}
}
}

#endif
