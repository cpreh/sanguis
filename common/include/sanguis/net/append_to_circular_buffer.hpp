#ifndef SANGUIS_NET_APPEND_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_APPEND_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>


namespace sanguis::net
{

[[nodiscard]]
SANGUIS_COMMON_SYMBOL
bool
append_to_circular_buffer(
	alda::net::buffer::circular_send::streambuf &, // NOLINT(google-runtime-references)
	sanguis::net::data_buffer const &
);

}

#endif
