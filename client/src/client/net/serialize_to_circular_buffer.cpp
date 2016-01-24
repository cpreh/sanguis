#include <sanguis/client/net/serialize_to_circular_buffer.hpp>
#include <sanguis/messages/client/base_fwd.hpp>
#include <sanguis/net/serialize_to_circular_buffer.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>


bool
sanguis::client::net::serialize_to_circular_buffer(
	sanguis::messages::client::base const &_message,
	alda::net::buffer::circular_send::object &_buffer
)
{
	return
		sanguis::net::serialize_to_circular_buffer(
			_message,
			_buffer
		);
}
