#ifndef SANGUIS_NET_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_NET_DESERIALIZE_HPP_INCLUDED

#include <sanguis/messages/auto_ptr.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>


namespace sanguis
{
namespace net
{

sanguis::messages::auto_ptr
deserialize(
	alda::net::buffer::circular_receive::object &
);

}
}

#endif
