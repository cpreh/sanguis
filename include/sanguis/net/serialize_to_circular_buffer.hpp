#ifndef SANGUIS_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/messages/base_fwd.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>


namespace sanguis
{
namespace net
{

bool
serialize_to_circular_buffer(
	sanguis::messages::base const &,
	alda::net::buffer::circular_send::object &
);

}
}

#endif
