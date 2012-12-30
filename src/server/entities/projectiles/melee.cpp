#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/projectiles/indeterminate.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/melee.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>


sanguis::server::entities::projectiles::melee::melee(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::team const _team,
	sanguis::server::damage::unit const _damage
)
:
	sanguis::server::entities::projectiles::projectile(
		_diff_clock,
		sanguis::projectile_type::melee,
		_team,
		sanguis::server::entities::movement_speed(
			0.f
		),
		sanguis::server::dim(
			1,
			1
		),
		sanguis::server::entities::projectiles::life_time(
			sanguis::duration_second(
				1.f
			)
		), // short lifetime
		sanguis::server::direction(
			0.f
		),
		sanguis::server::entities::projectiles::indeterminate::yes
	),
	damage_(
		_damage
	)
{
}

sanguis::server::entities::projectiles::melee::~melee()
{
}

void
sanguis::server::entities::projectiles::melee::do_damage(
	sanguis::server::entities::with_health &_entity
)
{
	_entity.damage(
		damage_,
		sanguis::server::damage::list(
			sanguis::server::damage::normal =
				sanguis::server::damage::full
		)
	);

	this->expire();
}
