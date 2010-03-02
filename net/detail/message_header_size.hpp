#ifndef SANGUIS_NET_DETAIL_MESSAGE_HEADER_SIZE_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_MESSAGE_HEADER_SIZE_HPP_INCLUDED

#include "message_header.hpp"
#include "../data_type.hpp"
#include <fcppt/container/raw_vector_decl.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{

data_type::size_type const
message_header_size(
	sizeof(message_header)
);

}
}
}

#endif
