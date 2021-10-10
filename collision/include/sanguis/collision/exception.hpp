#ifndef SANGUIS_COLLISION_EXCEPTION_HPP_INCLUDED
#define SANGUIS_COLLISION_EXCEPTION_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/symbol/class.hpp>

namespace sanguis::collision
{

class FCPPT_SYMBOL_CLASS exception : public fcppt::exception
{
public:
  SANGUIS_COLLISION_SYMBOL
  explicit exception(fcppt::string &&);

  SANGUIS_COLLISION_SYMBOL
  exception(exception &&) noexcept;

  SANGUIS_COLLISION_SYMBOL
  exception(exception const &);

  SANGUIS_COLLISION_SYMBOL
  exception &operator=(exception &&) noexcept;

  SANGUIS_COLLISION_SYMBOL
  exception &operator=(exception const &);

  SANGUIS_COLLISION_SYMBOL
  ~exception() noexcept override;
};

}

#endif
