#include <sanguis/perk_type.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/constant_damage_change.hpp>
#include <sanguis/server/perks/fire_damage.hpp>
#include <sanguis/server/perks/level_diff.hpp>

sanguis::server::perks::fire_damage::fire_damage()
    : sanguis::server::perks::perk(sanguis::perk_type::fire_damage)
{
}

sanguis::server::perks::fire_damage::~fire_damage() = default;

void sanguis::server::perks::fire_damage::change(
    sanguis::server::entities::with_perks &_entity, sanguis::server::perks::level_diff const _diff)
{
  sanguis::server::perks::constant_damage_change(
      _entity,
      sanguis::server::damage::type::fire,
      _diff,
      sanguis::server::perks::change_factor(
          0.3F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));
}
