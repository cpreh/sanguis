#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/piercing.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/text.hpp>


sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::damage::unit const _damage,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::projectiles::projectile(
		_diff_clock,
		sanguis::projectile_type::simple_bullet,
		_team,
		sanguis::server::entities::movement_speed(
			500.f
		),
		sanguis::server::model_name(
			FCPPT_TEXT("bullet")
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
		sanguis::server::damage::list{
			sanguis::server::damage::piercing =
				sanguis::server::damage::full
		}
	);

	this->expire();
}
