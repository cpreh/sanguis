#include <sanguis/duration_second.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/dual_pistols.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sanguis::server::weapons::unique_ptr sanguis::server::weapons::factory::dual_pistols(
    sanguis::server::weapons::factory::parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sanguis::server::weapons::weapon>(
      fcppt::make_unique_ptr<sanguis::server::weapons::pistol>(
          _parameters.common_parameters(),
          _parameters.weapon_type(),
          sanguis::server::weapons::pistol_parameters(
              sanguis::server::weapons::accuracy(
                  0.75F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ),
              sanguis::server::weapons::backswing_time(sanguis::duration_second(
                  0.13F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )),
              sanguis::server::weapons::damage(
                  5.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ),
              sanguis::server::weapons::cast_point(sanguis::duration_second(
                  0.2F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )),
              sanguis::server::weapons::magazine_size(
                  36U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ),
              sanguis::server::weapons::reload_time(sanguis::duration_second(
                  4.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )),
              sanguis::server::weapons::range(
                  1000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ))));
}
