#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/net/health_policy.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/diff.hpp>

sanguis::duration sanguis::server::net::health_policy::start_duration()
{
  return sanguis::duration_second(
      0.5F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );
}

sanguis::duration sanguis::server::net::health_policy::difference(
    sanguis::server::health const _health1, sanguis::server::health const _health2)
{
  return sanguis::duration_second(
      fcppt::math::diff(
          _health1.get(),
          _health2.get()) /
      fcppt::literal<sanguis::server::space_unit>(
          10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));
}
