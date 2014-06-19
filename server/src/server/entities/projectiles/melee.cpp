#include <sanguis/server/aoe.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/entities/projectiles/melee.hpp>


sanguis::server::entities::projectiles::melee::melee(
	sanguis::server::team const _team,
	sanguis::server::damage::unit const _damage,
	sanguis::server::damage::array const &_damage_values
)
:
	sanguis::server::entities::projectiles::aoe_damage(
		_team,
		sanguis::server::aoe(
			1.f
		),
		_damage,
		_damage_values
	)
{
}

sanguis::server::entities::projectiles::melee::~melee()
{
}
