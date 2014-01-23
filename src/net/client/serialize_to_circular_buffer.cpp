#include <sanguis/messages/client/base_fwd.hpp>
#include <sanguis/messages/client/serialization/serialize.hpp>
#include <sanguis/net/serialize_to_circular_buffer.hpp>
#include <sanguis/net/client/serialize_to_circular_buffer.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>


bool
sanguis::net::client::serialize_to_circular_buffer(
	sanguis::messages::client::base const &_message,
	alda::net::buffer::circular_send::object &_buffer
)
{
	return
		sanguis::net::serialize_to_circular_buffer(
			_message,
			_buffer,
			&sanguis::messages::client::serialization::serialize
		);
}
