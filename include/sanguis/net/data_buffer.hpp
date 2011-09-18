#ifndef SANGUIS_NET_DATA_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_DATA_BUFFER_HPP_INCLUDED

#include <sanguis/net/value_type.hpp>
#include <fcppt/container/raw_vector_fwd.hpp>

namespace sanguis
{
namespace net
{

typedef fcppt::container::raw_vector<
	net::value_type
> data_buffer;

}
}

#endif
