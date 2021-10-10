#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_ACCURACY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_ACCURACY_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons::modifiers
{

struct accuracy
{
  template <typename Parameters>
  static void make(
      sanguis::random_generator &_random_generator, // NOLINT(google-runtime-references)
      sanguis::server::entities::enemies::difficulty const _difficulty,
      fcppt::reference<Parameters> const _parameters)
  {
    _parameters.get().extra_accuracy(std::min(
        sanguis::server::weapons::accuracy(
            1.F -
            std::exp(
                -std::sqrt(sanguis::server::weapons::modifiers::random_increase(
                    _random_generator,
                    _difficulty)) /
                100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                )),
        sanguis::server::weapons::accuracy(1.F)));
  }
};

}

#endif
