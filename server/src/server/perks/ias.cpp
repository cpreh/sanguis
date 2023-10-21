#include <sanguis/perk_type.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/property/always_max.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/entities/property/linear_change.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/change_simple.hpp>
#include <sanguis/server/perks/ias.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>

sanguis::server::perks::ias::ias() : sanguis::server::perks::perk(sanguis::perk_type::ias) {}

sanguis::server::perks::ias::~ias() = default;

void sanguis::server::perks::ias::change(
    sanguis::server::entities::with_perks &_entity, sanguis::server::perks::level_diff const _diff)
{
  sanguis::server::perks::change_simple(
      &sanguis::server::entities::property::linear_change,
      _entity.attack_speed(),
      sanguis::server::perks::change_factor(
          0.2F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ),
      _diff);
}
