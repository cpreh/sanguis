#include <sanguis/net/receive_buffer_size.hpp>
#include <alda/net/buffer/max_receive_size.hpp>

alda::net::buffer::max_receive_size sanguis::net::receive_buffer_size()
{
  return alda::net::buffer::max_receive_size(
      128U * 1024U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );
}
