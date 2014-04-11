#ifndef SANGUIS_NET_SEND_BUFFER_SIZE_HPP_INCLUDED
#define SANGUIS_NET_SEND_BUFFER_SIZE_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <alda/net/buffer/max_send_size.hpp>


namespace sanguis
{
namespace net
{

SANGUIS_COMMON_SYMBOL
alda::net::buffer::max_send_size const
send_buffer_size();

}
}

#endif