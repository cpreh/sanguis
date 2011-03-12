#ifndef SANGUIS_NET_SERIALIZE_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_HPP_INCLUDED

#include "../messages/auto_ptr.hpp"
#include "data_type.hpp"

namespace sanguis
{
namespace net
{

void
serialize(
	messages::auto_ptr,
	net::data_type &
);

}
}

#endif