#ifndef SANGUIS_CREATOR_EXCEPTION_HPP_INCLUDED
#define SANGUIS_CREATOR_EXCEPTION_HPP_INCLUDED

#include <sanguis/creator/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/symbol/class.hpp>

namespace sanguis::creator
{

class FCPPT_SYMBOL_CLASS exception : public fcppt::exception
{
public:
  SANGUIS_CREATOR_SYMBOL
  explicit exception(fcppt::string &&);

  SANGUIS_CREATOR_SYMBOL
  exception(exception &&) noexcept;

  SANGUIS_CREATOR_SYMBOL
  exception(exception const &);

  SANGUIS_CREATOR_SYMBOL
  exception &operator=(exception &&) noexcept;

  SANGUIS_CREATOR_SYMBOL
  exception &operator=(exception const &);

  SANGUIS_CREATOR_SYMBOL
  ~exception() noexcept override;
};

}

#endif
