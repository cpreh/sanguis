#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_SPREAD_RADIUS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_SPREAD_RADIUS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/spread_radius.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/math/div.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons::modifiers
{

struct spread_radius
{
  template <typename Parameters>
  static void make(
      sanguis::random_generator &_random_generator, // NOLINT(google-runtime-references)
      sanguis::server::entities::enemies::difficulty const _difficulty,
      fcppt::reference<Parameters> const _parameters)
  {
    _parameters.get().extra_spread_radius(-std::max(
        fcppt::optional::maybe(
            fcppt::math::div(
                _parameters.get().spread_radius().base().get(),
                std::sqrt(sanguis::server::weapons::modifiers::random_increase(
                    _random_generator, _difficulty))),
            fcppt::const_(sanguis::server::weapons::spread_radius(0.F)),
            [](sanguis::server::space_unit const _div)
            { return sanguis::server::weapons::spread_radius{_div}; }),
        sanguis::server::weapons::spread_radius(0.F)));
  }
};

}

#endif
