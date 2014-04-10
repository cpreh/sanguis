#ifndef SANGUIS_NET_APPEND_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_APPEND_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/net/data_buffer_fwd.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>


namespace sanguis
{
namespace net
{

SANGUIS_COMMON_SYMBOL
bool
append_to_circular_buffer(
	alda::net::buffer::circular_send::object &,
	sanguis::net::data_buffer const &
);

}
}

#endif
