#ifndef SANGUIS_CLIENT_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_CLIENT_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/messages/client/base_fwd.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>

namespace sanguis::client::net
{

[[nodiscard]] bool serialize_to_circular_buffer(
    sanguis::messages::client::base const &,
    alda::net::buffer::circular_send::streambuf & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
