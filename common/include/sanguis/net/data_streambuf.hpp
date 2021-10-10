#ifndef SANGUIS_NET_DATA_STREAMBUF_HPP_INCLUDED
#define SANGUIS_NET_DATA_STREAMBUF_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/net/data_buffer.hpp>
#include <sanguis/net/data_streambuf_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <streambuf>
#include <fcppt/config/external_end.hpp>

namespace sanguis::net
{

class data_streambuf : public std::streambuf
{
  FCPPT_NONMOVABLE(data_streambuf);

public:
  SANGUIS_COMMON_SYMBOL
  explicit data_streambuf(fcppt::reference<sanguis::net::data_buffer>);

  SANGUIS_COMMON_SYMBOL
  ~data_streambuf() override;

private:
  [[nodiscard]] std::streamsize xsputn(char_type const *, std::streamsize) override;

  [[nodiscard]] int_type overflow(int_type) override;

  fcppt::reference<sanguis::net::data_buffer> const buffer_;
};

}

#endif
