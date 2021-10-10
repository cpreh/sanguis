#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/apply.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters.hpp>
#include <fcppt/make_ref.hpp>

sanguis::server::entities::enemies::attribute_container
sanguis::server::entities::enemies::modifiers::apply(
    sanguis::random_generator &_random_generator,
    fcppt::reference<sanguis::server::entities::enemies::parameters> const _parameters,
    sanguis::server::entities::enemies::modifiers::container const &_modifiers)
{
  sanguis::server::entities::enemies::attribute_container result{};

  result.reserve(_modifiers.size());

  sanguis::server::entities::enemies::modifiers::parameters const modifier_parameters(
      fcppt::make_ref(_random_generator));

  for (auto const &modifier : _modifiers)
  {
    result.push_back(modifier(_parameters, modifier_parameters));
  }

  return result;
}
