#include <sanguis/net/receive_buffer_size.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <fcppt/literal.hpp>

alda::net::buffer::max_receive_size sanguis::net::receive_buffer_size()
{
  return alda::net::buffer::max_receive_size{
      fcppt::literal<alda::net::size_type>(
          128U) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      * fcppt::literal<alda::net::size_type>(
            1024U) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  };
}
