#include <sanguis/server/entities/property/apply.hpp>
#include <sanguis/server/entities/property/base.hpp>
#include <sanguis/server/entities/property/linear_decrease.hpp>
#include <sanguis/server/entities/property/linear_decrease_op.hpp>
#include <sanguis/server/entities/property/value.hpp>

void sanguis::server::entities::property::linear_decrease_op(
    sanguis::server::entities::property::base &_base,
    sanguis::server::entities::property::value const _value,
    sanguis::server::entities::property::apply const _apply)
{
  sanguis::server::entities::property::linear_decrease old(_base.linear_decrease());

  if (_apply.get())
  {
    old.mul(_value);
  }
  else
  {
    old.div(_value);
  }

  _base.linear_decrease(old);
}
