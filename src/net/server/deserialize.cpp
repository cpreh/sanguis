#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/messages/server/serialization/deserialize.hpp>
#include <sanguis/net/deserialize.hpp>
#include <sanguis/net/server/deserialize.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>


sanguis::messages::server::unique_ptr
sanguis::net::server::deserialize(
	alda::net::buffer::circular_receive::object &_buffer
)
{
	return
		sanguis::net::deserialize(
			_buffer,
			&sanguis::messages::server::serialization::deserialize
		);
}
