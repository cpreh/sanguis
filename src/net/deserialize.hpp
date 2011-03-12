#ifndef SANGUIS_NET_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_NET_DESERIALIZE_HPP_INCLUDED

#include "../messages/auto_ptr.hpp"
#include "data_type.hpp"

namespace sanguis
{
namespace net
{

messages::auto_ptr
deserialize(
	net::data_type &
);

}
}

#endif
