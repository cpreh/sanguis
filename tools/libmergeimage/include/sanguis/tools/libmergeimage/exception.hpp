#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_EXCEPTION_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_EXCEPTION_HPP_INCLUDED

#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>

namespace sanguis::tools::libmergeimage
{

class exception : public fcppt::exception
{
public:
  explicit exception(fcppt::string &&);

  exception(exception &&) noexcept;

  exception(exception const &);

  exception &operator=(exception &&) noexcept;

  exception &operator=(exception const &);

  ~exception() noexcept override;
};

}

#endif
