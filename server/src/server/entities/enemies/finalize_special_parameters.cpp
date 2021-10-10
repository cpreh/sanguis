#include <sanguis/server/exp.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/finalize_special_parameters.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/int_to_float.hpp>

sanguis::server::entities::enemies::parameters &
sanguis::server::entities::enemies::finalize_special_parameters(
    fcppt::reference<sanguis::server::entities::enemies::parameters> const _parameters,
    sanguis::server::entities::enemies::attribute_container const &_attributes,
    sanguis::server::entities::enemies::skills::factory::container const &_skills)
{
  // TODO(philipp): Assign variable factors to modifiers/skills
  auto const specials_factor(1U + _attributes.size() + _skills.size());

  return _parameters.get()
      .exp(
          _parameters->exp() *
          sanguis::server::exp(
              fcppt::cast::int_to_float<sanguis::server::exp::value_type>(specials_factor)))
      .pickup_probability(sanguis::server::pickup_probability(1.F))
      .difficulty(
          _parameters->difficulty() *
          sanguis::server::entities::enemies::difficulty(
              fcppt::cast::int_to_float<sanguis::server::entities::enemies::difficulty::value_type>(
                  specials_factor)));
}
