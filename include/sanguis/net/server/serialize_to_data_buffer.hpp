#ifndef SANGUIS_NET_SERVER_SERIALIZE_TO_DATA_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_SERVER_SERIALIZE_TO_DATA_BUFFER_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/net/data_buffer_fwd.hpp>


namespace sanguis
{
namespace net
{
namespace server
{

bool
serialize_to_data_buffer(
	sanguis::messages::server::base const &,
	sanguis::net::data_buffer &
);

}
}
}

#endif
