#ifndef SANGUIS_NET_MESSAGE_HEADER_SIZE_HPP_INCLUDED
#define SANGUIS_NET_MESSAGE_HEADER_SIZE_HPP_INCLUDED

#include "message_header.hpp"
#include "data_buffer.hpp"
#include <fcppt/container/raw_vector_decl.hpp>

namespace sanguis
{
namespace net
{

data_buffer::size_type const
message_header_size(
	sizeof(net::message_header)
);

}
}

#endif
