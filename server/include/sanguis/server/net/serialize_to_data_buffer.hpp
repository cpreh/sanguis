#ifndef SANGUIS_SERVER_NET_SERIALIZE_TO_DATA_BUFFER_HPP_INCLUDED
#define SANGUIS_SERVER_NET_SERIALIZE_TO_DATA_BUFFER_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/net/data_buffer.hpp>

namespace sanguis::server::net
{

void serialize_to_data_buffer(
    sanguis::messages::server::base const &,
    sanguis::net::data_buffer & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
