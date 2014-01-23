#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/messages/client/serialization/deserialize.hpp>
#include <sanguis/net/deserialize.hpp>
#include <sanguis/net/client/deserialize.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>


sanguis::messages::client::unique_ptr
sanguis::net::client::deserialize(
	alda::net::buffer::circular_receive::object &_buffer
)
{
	return
		sanguis::net::deserialize(
			_buffer,
			&sanguis::messages::client::serialization::deserialize
		);
}
