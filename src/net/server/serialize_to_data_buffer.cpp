#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/serialization/serialize.hpp>
#include <sanguis/net/data_buffer_fwd.hpp>
#include <sanguis/net/serialize_to_data_buffer.hpp>
#include <sanguis/net/server/serialize_to_data_buffer.hpp>


bool
sanguis::net::server::serialize_to_data_buffer(
	sanguis::messages::server::base const &_message,
	sanguis::net::data_buffer &_buffer
)
{
	return
		sanguis::net::serialize_to_data_buffer(
			_message,
			_buffer,
			&sanguis::messages::server::serialization::serialize
		);
}
