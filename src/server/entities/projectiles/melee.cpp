#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/entities/projectiles/melee.hpp>


sanguis::server::entities::projectiles::melee::melee(
	sanguis::server::team const _team,
	sanguis::server::damage::unit const _damage
)
:
	sanguis::server::entities::projectiles::aoe_damage(
		_team,
		sanguis::server::radius(
			1.f
		),
		_damage,
		sanguis::server::damage::list(
			sanguis::server::damage::normal =
				sanguis::server::damage::full
		)
	)
{
}

sanguis::server::entities::projectiles::melee::~melee()
{
}
