#ifndef SANGUIS_SERVER_NET_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_SERVER_NET_DESERIALIZE_HPP_INCLUDED

#include <sanguis/messages/client/optional_unique_ptr.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

sanguis::messages::client::optional_unique_ptr
deserialize(
	alda::net::buffer::circular_receive::object &
);

}
}
}

#endif
