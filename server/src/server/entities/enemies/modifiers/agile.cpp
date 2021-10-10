#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/agile.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp>
#include <sanguis/server/weapons/ias.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::enemies::attribute sanguis::server::entities::enemies::modifiers::agile(
    fcppt::reference<sanguis::server::entities::enemies::parameters> const _parameters,
    sanguis::server::entities::enemies::modifiers::parameters const &)
{
  _parameters->ias(sanguis::server::weapons::ias(
      _parameters->ias().get() * std::sqrt(_parameters->difficulty().get())));

  _parameters->irs(sanguis::server::weapons::irs(
      _parameters->irs().get() * std::sqrt(_parameters->difficulty().get())));

  return sanguis::server::entities::enemies::attribute(FCPPT_TEXT("agile"));
}
