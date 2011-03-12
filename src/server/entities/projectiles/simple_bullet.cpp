#include "simple_bullet.hpp"
#include "../with_health.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/piercing.hpp"
#include "../../damage/full.hpp"
#include "../../environment/load_context.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	server::environment::load_context_ptr const _load_context,
	team::type const _team,
	damage::unit const _damage,
	space_unit const _direction
)
:
	projectile(
		projectile_type::simple_bullet,
		_team,
		entities::movement_speed(
			500
		),
		_load_context->entity_dim(
			FCPPT_TEXT("bullet")
		),
		life_time(
			10
		),
		_direction,
		indeterminate::no
	),
	damage_(_damage)
{}

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

	expire();
}
