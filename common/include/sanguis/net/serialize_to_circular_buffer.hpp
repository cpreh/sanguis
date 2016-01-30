#ifndef SANGUIS_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/net/message_header.hpp>
#include <alda/message/base_fwd.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <alda/net/buffer/circular_send/put_message.hpp>


namespace sanguis
{
namespace net
{

template<
	typename AldaType
>
inline
bool
serialize_to_circular_buffer(
	alda::message::base<
		AldaType
	> const &_message,
	alda::net::buffer::circular_send::object &_buffer
)
{
	return
		alda::net::buffer::circular_send::put_message<
			sanguis::net::message_header
		>(
			_message,
			_buffer
		);
}

}
}

#endif
