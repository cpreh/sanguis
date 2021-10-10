#include <sanguis/server/entities/property/linear_decrease.hpp>
#include <sanguis/server/entities/property/value.hpp>

sanguis::server::entities::property::linear_decrease::linear_decrease() : value_(1) {}

void sanguis::server::entities::property::linear_decrease::mul(
    sanguis::server::entities::property::value const _mul)
{
  value_ *= _mul;
}

void sanguis::server::entities::property::linear_decrease::div(
    sanguis::server::entities::property::value const _div)
{
  value_ /= _div;
}

sanguis::server::entities::property::value
sanguis::server::entities::property::linear_decrease::value() const
{
  return value_;
}
