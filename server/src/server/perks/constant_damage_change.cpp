#include <sanguis/server/damage/type_fwd.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/property/always_max.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/entities/property/constant_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/constant_damage_change.hpp>
#include <sanguis/server/perks/level_diff.hpp>

void sanguis::server::perks::constant_damage_change(
    sanguis::server::entities::with_perks &_entity,
    sanguis::server::damage::type const _type,
    sanguis::server::perks::level_diff const _diff,
    sanguis::server::perks::change_factor const _factor)
{
  sanguis::server::perks::change_simple(
      &sanguis::server::entities::property::constant_change,
      _entity.extra_damage(_type),
      _factor,
      _diff);
}
