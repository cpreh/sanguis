#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <sanguis/net/serialize_to_data_buffer.hpp>
#include <sanguis/server/net/serialize_to_data_buffer.hpp>

void sanguis::server::net::serialize_to_data_buffer(
    sanguis::messages::server::base const &_message, sanguis::net::data_buffer &_buffer)
{
  sanguis::net::serialize_to_data_buffer(_message, _buffer);
}
