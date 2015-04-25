#include <sanguis/duration_second.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>


sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::damage::unit const _damage,
	sanguis::server::damage::modified_array const &_damage_modifiers,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::projectiles::projectile(
		sanguis::projectile_type::bullet,
		_team,
		sanguis::server::entities::movement_speed(
			500.f
		),
		_load_context,
		sanguis::server::entities::projectiles::life_time(
			sanguis::duration_second(
				10.f
			)
		),
		_direction
	),
	damage_(
		_damage
	),
	damage_modifiers_(
		_damage_modifiers
	)
{
}

sanguis::server::entities::projectiles::simple_bullet::~simple_bullet()
{
}

void
sanguis::server::entities::projectiles::simple_bullet::do_damage(
	sanguis::server::entities::with_health &_entity
)
{
	_entity.damage(
		damage_,
		damage_modifiers_
	);

	this->expire();
}
