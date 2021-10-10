#include <sanguis/server/entities/property/constant.hpp>
#include <sanguis/server/entities/property/value.hpp>

sanguis::server::entities::property::constant::constant() : value_(0) {}

void sanguis::server::entities::property::constant::change(
    sanguis::server::entities::property::value const _add)
{
  value_ += _add;
}

sanguis::server::entities::property::value
sanguis::server::entities::property::constant::value() const
{
  return value_;
}
