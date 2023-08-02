#include <sanguis/net/send_buffer_size.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <fcppt/literal.hpp>

alda::net::buffer::max_send_size sanguis::net::send_buffer_size()
{
  return alda::net::buffer::max_send_size{
      fcppt::literal<alda::net::size_type>(1024U) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      * fcppt::literal<alda::net::size_type>(64U) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  };
}
