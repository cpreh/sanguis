#include <sanguis/buff_type.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <sanguis/server/entities/with_velocity.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/entities/with_velocity_ref.hpp>
#include <sanguis/server/entities/property/apply.hpp>
#include <sanguis/server/entities/property/linear_decrease_op.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/cast/static_downcast.hpp>

sanguis::server::buffs::slow::slow(
    sanguis::server::entities::with_velocity_ref const _entity,
    sanguis::server::buffs::slow_factor const _factor)
    : sanguis::server::buffs::buff(), entity_(_entity), factor_(_factor)
{
}

sanguis::server::buffs::slow::~slow() = default;

sanguis::buff_type sanguis::server::buffs::slow::type() const { return sanguis::buff_type::slow; }

void sanguis::server::buffs::slow::apply(sanguis::server::buffs::buff::added const _added)
{
  sanguis::server::entities::property::linear_decrease_op(
      entity_->movement_speed(),
      factor_.get(),
      sanguis::server::entities::property::apply(_added.get()));
}

bool sanguis::server::buffs::slow::greater(sanguis::server::buffs::buff const &_other) const
{
  // Smaller factors mean greater slowdown
  return factor_ <
         fcppt::cast::static_downcast<sanguis::server::buffs::slow const &>(_other).factor_;
}
