#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_HPP_INCLUDED

#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/actions/scale_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/control/actions/scale_type.hpp>

namespace sanguis::client::control::actions
{

class scale
{
public:
  scale(sanguis::client::control::actions::scale_type, sanguis::client::control::key_scale);

  [[nodiscard]] sanguis::client::control::actions::scale_type type() const;

  [[nodiscard]] sanguis::client::control::key_scale get() const;

private:
  sanguis::client::control::actions::scale_type type_;

  sanguis::client::control::key_scale scale_;
};

}

#endif
