#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <alda/net/buffer/circular_send/streambuf.hpp>
#include <alda/serialization/ostream.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>

bool sanguis::net::append_to_circular_buffer(
    alda::net::buffer::circular_send::streambuf &_dest, sanguis::net::data_buffer const &_src)
{
  if (_dest.space_left() < _src.size())
  {
    return false;
  }

  alda::serialization::ostream stream(&_dest);

  stream.write(
      _src.data(), fcppt::cast::size<std::streamsize>(fcppt::cast::to_signed(_src.size())));

  return true;
}
