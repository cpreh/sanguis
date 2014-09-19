#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>


sanguis::server::weapons::melee_parameters::melee_parameters(
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::backswing_time const _backswing_time,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::damage::array const &_damage_values
)
:
	range_{
		_range
	},
	backswing_time_{
		_backswing_time
	},
	damage_{
		_damage
	},
	damage_values_(
		_damage_values
	)
{
}

sanguis::server::weapons::backswing_time const
sanguis::server::weapons::melee_parameters::backswing_time() const
{
	return
		backswing_time_;
}

sanguis::server::weapons::attributes::damage const
sanguis::server::weapons::melee_parameters::damage() const
{
	return
		damage_;
}

sanguis::server::weapons::range const
sanguis::server::weapons::melee_parameters::range() const
{
	return
		range_;
}

sanguis::server::damage::array const &
sanguis::server::weapons::melee_parameters::damage_values() const
{
	return
		damage_values_;
}

void
sanguis::server::weapons::melee_parameters::extra_damage(
	sanguis::server::weapons::damage const _damage
)
{
	damage_.extra(
		_damage
	);
}
