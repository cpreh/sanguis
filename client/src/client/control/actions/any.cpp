#include <sanguis/client/control/actions/any.hpp>
#include <sanguis/client/control/actions/variant.hpp>

sanguis::client::control::actions::any::any(
    sanguis::client::control::actions::variant const _variant)
    : variant_(_variant)
{
}

sanguis::client::control::actions::variant const &
sanguis::client::control::actions::any::get() const
{
  return variant_;
}
