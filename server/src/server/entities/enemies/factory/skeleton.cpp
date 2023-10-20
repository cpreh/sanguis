#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/mass.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/burn_create.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/buffs/define_special.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/make_array.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_id.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/factory/make.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/skeleton.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/melee_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::with_id_unique_ptr sanguis::server::entities::enemies::factory::skeleton(
    sanguis::server::entities::enemies::factory::parameters const &_parameters)
{
  SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL(skeleton_burn, burn);

  return sanguis::server::entities::enemies::factory::make(
      _parameters,
      sanguis::server::damage::no_armor(),
      sanguis::server::mass{
          20.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          * boost::units::si::kilogram},
      sanguis::server::health(
          12.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          * std::sqrt(_parameters.difficulty().get())),
      sanguis::server::entities::movement_speed(
          50.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      sanguis::server::ai::create_simple(
          fcppt::make_ref(_parameters.random_generator()),
          sanguis::server::ai::sight_range(
              1000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              )),
      fcppt::unique_ptr_to_base<
          sanguis::server::weapons::weapon>(fcppt::make_unique_ptr<sanguis::server::weapons::melee>(
          _parameters.weapon_parameters(),
          sanguis::server::weapons::melee_parameters{
              sanguis::server::weapons::range(
                  100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ),
              sanguis::server::weapons::backswing_time(sanguis::duration_second(1.F)),
              sanguis::server::weapons::damage(
                  10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ),
              sanguis::server::damage::make_array(
                  {sanguis::server::damage::normal = sanguis::server::damage::full})})),
      sanguis::server::pickup_probability(
          0.75F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      sanguis::server::exp(
          100.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      fcppt::container::make<sanguis::server::auras::container>(
          sanguis::server::auras::burn_create<skeleton_burn>(
              sanguis::server::radius(
                  300.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ),
              sanguis::server::team::monsters,
              sanguis::server::buffs::burn_interval(sanguis::duration_second(1.F)),
              sanguis::server::damage::unit(1.F * std::sqrt(_parameters.difficulty().get())))));
}
