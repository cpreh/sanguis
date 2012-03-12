#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/piercing.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/duration_second.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	sanguis::diff_clock const &_diff_clock,
	server::environment::load_context &_load_context,
	server::team::type const _team,
	damage::unit const _damage,
	server::direction const _direction
)
:
	projectile(
		_diff_clock,
		projectile_type::simple_bullet,
		_team,
		entities::movement_speed(
			10.f
		),
		_load_context.entity_dim(
			FCPPT_TEXT("bullet")
		),
		projectiles::life_time(
			sanguis::duration_second(
				10.f
			)
		),
		_direction,
		indeterminate::no
	),
	damage_(_damage)
{
}

sanguis::server::entities::projectiles::simple_bullet::~simple_bullet()
{
}

void
sanguis::server::entities::projectiles::simple_bullet::do_damage(
	with_health &_entity
)
{
	_entity.damage(
		damage_,
		damage::list(
			damage::piercing = damage::full
		)
	);

	this->expire();
}
