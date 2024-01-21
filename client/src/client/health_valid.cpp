#include <sanguis/client/health.hpp>
#include <sanguis/client/health_valid.hpp>
#include <sanguis/client/health_value.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep

bool sanguis::client::health_valid(sanguis::client::health const _health)
{
  return _health >= sanguis::client::health(fcppt::literal<sanguis::client::health_value>(0));
}
