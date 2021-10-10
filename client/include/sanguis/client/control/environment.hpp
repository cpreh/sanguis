#ifndef SANGUIS_CLIENT_CONTROL_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/client/control/cursor_position_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/control/optional_attack_dest_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::control
{

class environment
{
  FCPPT_NONMOVABLE(environment);

protected:
  environment();

public:
  [[nodiscard]] virtual sanguis::client::control::optional_attack_dest
  translate_attack_dest(sanguis::client::control::cursor_position const &) const = 0;

  virtual ~environment();
};

}

#endif
