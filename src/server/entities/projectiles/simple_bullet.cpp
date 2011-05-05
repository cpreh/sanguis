#include "simple_bullet.hpp"
#include "../with_health.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/piercing.hpp"
#include "../../damage/full.hpp"
#include "../../environment/load_context.hpp"
#include "../../../time_from_second.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	server::environment::load_context &_load_context,
	server::team::type const _team,
	damage::unit const _damage,
	server::direction const _direction
)
:
	projectile(
		projectile_type::simple_bullet,
		_team,
		entities::movement_speed(
			10
		),
		_load_context.entity_dim(
			FCPPT_TEXT("bullet")
		),
		projectiles::life_time(
			sanguis::time_from_second(
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
