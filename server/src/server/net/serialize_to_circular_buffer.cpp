#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/net/serialize_to_circular_buffer.hpp>
#include <sanguis/server/net/serialize_to_circular_buffer.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>

bool sanguis::server::net::serialize_to_circular_buffer(
    sanguis::messages::server::base const &_message,
    alda::net::buffer::circular_send::streambuf &_buffer)
{
  return sanguis::net::serialize_to_circular_buffer(_message, _buffer);
}
