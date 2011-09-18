#ifndef SANGUIS_NET_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/net/value_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace net
{

typedef boost::circular_buffer<
	net::value_type
> circular_buffer;

}
}

#endif
