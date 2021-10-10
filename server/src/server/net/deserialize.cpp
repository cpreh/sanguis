#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/optional_unique_ptr.hpp>
#include <sanguis/messages/client/serialization/context.hpp>
#include <sanguis/messages/client/serialization/details.hpp>
#include <sanguis/messages/client/serialization/global_context.hpp>
#include <sanguis/net/deserialize.hpp>
#include <sanguis/server/net/deserialize.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>

sanguis::messages::client::optional_unique_ptr
sanguis::server::net::deserialize(alda::net::buffer::circular_receive::streambuf &_buffer)
{
  return sanguis::net::deserialize(
      sanguis::messages::client::serialization::global_context(), _buffer);
}
