#include <sanguis/client/net/deserialize.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/optional_unique_ptr.hpp>
#include <sanguis/messages/server/serialization/context.hpp>
#include <sanguis/messages/server/serialization/details.hpp>
#include <sanguis/messages/server/serialization/global_context.hpp>
#include <sanguis/net/deserialize.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>

sanguis::messages::server::optional_unique_ptr
sanguis::client::net::deserialize(alda::net::buffer::circular_receive::streambuf &_buffer)
{
  return sanguis::net::deserialize(
      sanguis::messages::server::serialization::global_context(), _buffer);
}
