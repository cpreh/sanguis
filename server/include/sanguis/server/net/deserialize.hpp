#ifndef SANGUIS_SERVER_NET_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_SERVER_NET_DESERIALIZE_HPP_INCLUDED

#include <sanguis/messages/client/unique_ptr.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>


namespace sanguis
{
namespace net
{
namespace server
{

sanguis::messages::client::unique_ptr
deserialize(
	alda::net::buffer::circular_receive::object &
);

}
}
}

#endif
