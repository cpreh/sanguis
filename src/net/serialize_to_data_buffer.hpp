#ifndef SANGUIS_NET_SERIALIZE_TO_DATA_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_TO_DATA_BUFFER_HPP_INCLUDED

#include "data_buffer.hpp"
#include "../messages/auto_ptr.hpp"

namespace sanguis
{
namespace net
{

bool
serialize_to_data_buffer(
	messages::auto_ptr,
	net::data_buffer &
);

}
}

#endif