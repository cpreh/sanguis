#include <sanguis/random_generator.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/weapons/modifiers/random_amount.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/type_iso/strong_typedef.hpp> // NOLINT(misc-include-cleaner)

sanguis::server::random::amount sanguis::server::weapons::modifiers::random_amount(
    sanguis::random_generator &_random_generator, sanguis::server::random::amount const _max)
{
  using parameters =
      fcppt::random::distribution::parameters::uniform_int<sanguis::server::random::amount>;

  auto distribution(fcppt::random::distribution::make_basic(
      parameters(parameters::min(sanguis::server::random::amount(0U)), parameters::max(_max))));

  return distribution(_random_generator);
}
