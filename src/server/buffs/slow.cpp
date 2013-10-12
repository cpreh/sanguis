#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/linear_decrease_op.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/cast/static_downcast.hpp>


sanguis::server::buffs::slow::slow(
	sanguis::server::buffs::slow::factor const _factor
)
:
	sanguis::server::buffs::buff(),
	factor_(
		_factor
	)
{
}

sanguis::server::buffs::slow::~slow()
{
}

void
sanguis::server::buffs::slow::apply(
	sanguis::server::entities::base &_entity,
	sanguis::server::buffs::buff::added const _added
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_velocity *,
		with_velocity,
		&_entity
	)
		sanguis::server::entities::property::linear_decrease_op(
			with_velocity->movement_speed(),
			factor_.get(),
			sanguis::server::entities::property::apply(
				_added.get()
			)
		);
}

bool
sanguis::server::buffs::slow::less(
	sanguis::server::buffs::buff const &_other
) const
{
	return
		factor_
		<
		fcppt::cast::static_downcast<
			sanguis::server::buffs::slow const &
		>(
			_other
		).factor_;
}
