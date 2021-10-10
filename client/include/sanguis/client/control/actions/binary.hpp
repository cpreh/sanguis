#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_BINARY_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_BINARY_HPP_INCLUDED

#include <sanguis/client/control/actions/binary_fwd.hpp>
#include <sanguis/client/control/actions/binary_type.hpp>

namespace sanguis::client::control::actions
{

class binary
{
public:
  binary(sanguis::client::control::actions::binary_type, bool);

  [[nodiscard]] sanguis::client::control::actions::binary_type type() const;

  [[nodiscard]] bool value() const;

private:
  sanguis::client::control::actions::binary_type type_;

  bool value_;
};

}

#endif
