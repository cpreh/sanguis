#ifndef SANGUIS_NET_DATA_TYPE_HPP_INCLUDED
#define SANGUIS_NET_DATA_TYPE_HPP_INCLUDED

#include "value_type.hpp"
#include <fcppt/container/raw_vector_fwd.hpp>

namespace sanguis
{
namespace net
{

typedef fcppt::container::raw_vector<
	net::value_type
> data_type;

}
}

#endif // SANGUIS_NET_DATA_TYPE_HPP_INCLUDED
