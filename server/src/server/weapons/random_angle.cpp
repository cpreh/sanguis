#include <sanguis/random_generator.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/random_angle.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/normal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <numbers>
#include <fcppt/config/external_end.hpp>

sanguis::server::angle sanguis::server::weapons::random_angle(
    sanguis::random_generator &_random_generator,
    sanguis::server::weapons::accuracy const _accuracy,
    sanguis::server::angle const _angle)
{
  sanguis::server::space_unit const spread(
      (fcppt::literal<sanguis::server::space_unit>(1) - _accuracy.get()) *
      std::numbers::pi_v<sanguis::server::space_unit> /
      fcppt::literal<sanguis::server::space_unit>(
          4 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));

  using normal_distribution =
      fcppt::random::distribution::parameters::normal<sanguis::server::space_unit>;

  auto angle_distribution(fcppt::random::distribution::make_basic(normal_distribution(
      normal_distribution::mean(_angle.get()), normal_distribution::stddev(spread))));

  return sanguis::server::angle(angle_distribution(_random_generator));
}
