#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_ANY_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_ANY_HPP_INCLUDED

#include <sanguis/client/control/actions/any_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/control/actions/variant.hpp>

namespace sanguis::client::control::actions
{

class any
{
public:
  explicit any(sanguis::client::control::actions::variant);

  [[nodiscard]] sanguis::client::control::actions::variant const &get() const;

private:
  sanguis::client::control::actions::variant variant_;
};

}

#endif
