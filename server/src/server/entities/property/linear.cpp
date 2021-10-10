#include <sanguis/server/entities/property/linear.hpp>
#include <sanguis/server/entities/property/value.hpp>

sanguis::server::entities::property::linear::linear() : value_(1) {}

void sanguis::server::entities::property::linear::change(
    sanguis::server::entities::property::value const _add)
{
  value_ += _add;
}

sanguis::server::entities::property::value
sanguis::server::entities::property::linear::value() const
{
  return value_;
}
