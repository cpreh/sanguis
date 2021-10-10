#include <sanguis/random_generator.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

sanguis::server::space_unit sanguis::server::weapons::modifiers::random_increase(
    sanguis::random_generator &_random_generator,
    sanguis::server::entities::enemies::difficulty const _difficulty)
{
  using parameters =
      fcppt::random::distribution::parameters::uniform_real<sanguis::server::space_unit>;

  auto distribution(fcppt::random::distribution::make_basic(
      parameters(parameters::min(1.F), parameters::sup(std::sqrt(std::sqrt(_difficulty.get()))))));

  return distribution(_random_generator);
}
