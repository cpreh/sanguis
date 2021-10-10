#ifndef SANGUIS_MODEL_EXCEPTION_HPP_INCLUDED
#define SANGUIS_MODEL_EXCEPTION_HPP_INCLUDED

#include <sanguis/model/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/symbol/class.hpp>

namespace sanguis::model
{

class FCPPT_SYMBOL_CLASS exception : public fcppt::exception
{
public:
  SANGUIS_MODEL_SYMBOL
  explicit exception(fcppt::string &&);

  SANGUIS_MODEL_SYMBOL
  exception(exception &&) noexcept;

  SANGUIS_MODEL_SYMBOL
  exception(exception const &);

  SANGUIS_MODEL_SYMBOL
  exception &operator=(exception &&) noexcept;

  SANGUIS_MODEL_SYMBOL
  exception &operator=(exception const &);

  SANGUIS_MODEL_SYMBOL
  ~exception() noexcept override;
};

}

#endif
