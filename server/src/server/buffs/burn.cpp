#include <sanguis/buff_type.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_health.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/entities/with_health_ref.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/cast/static_downcast.hpp>

sanguis::server::buffs::burn::burn(
    sanguis::server::entities::with_health_ref const _entity,
    sanguis::server::buffs::burn_interval const _interval,
    sanguis::server::damage::unit const _damage,
    sanguis::server::damage::modified_array const &_damage_values)
    : entity_(_entity),
      interval_timer_(sanguis::diff_timer::parameters(
          fcppt::make_cref(_entity->diff_clock()), _interval.get())),
      damage_(_damage),
      damage_values_(_damage_values)
{
}

sanguis::server::buffs::burn::~burn() = default;

sanguis::buff_type sanguis::server::buffs::burn::type() const { return sanguis::buff_type::burn; }

void sanguis::server::buffs::burn::update()
{
  if (sge::timer::reset_when_expired(fcppt::make_ref(interval_timer_)))
  {
    entity_->damage(damage_, damage_values_);
  }
}

bool sanguis::server::buffs::burn::greater(sanguis::server::buffs::buff const &_other) const
{
  return damage_ >
         fcppt::cast::static_downcast<sanguis::server::buffs::burn const &>(_other).damage_;
}
