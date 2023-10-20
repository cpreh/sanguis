#include <sanguis/server/health.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/health.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::enemies::attribute sanguis::server::entities::enemies::modifiers::health(
    fcppt::reference<sanguis::server::entities::enemies::parameters> const _parameters,
    sanguis::server::entities::enemies::modifiers::parameters const &)
{
  _parameters->health(
      _parameters->health() *
      sanguis::server::health(
          3.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));

  return sanguis::server::entities::enemies::attribute(FCPPT_TEXT("tough"));
}
