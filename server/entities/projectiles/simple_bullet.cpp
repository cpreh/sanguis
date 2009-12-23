#include "simple_bullet.hpp"
#include "../with_health.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/piercing.hpp"
#include "../../damage/full.hpp"
#include "../../environment/load_context.hpp"
#include <fcppt/text.hpp>

sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	server::environment::load_context_ptr const load_context,
	team::type const team_,
	damage::unit const damage_,
	space_unit const direction_
)
:
	projectile(
		projectile_type::simple_bullet,
		team_,
		entities::movement_speed(
			500
		),
		load_context->entity_dim(
			FCPPT_TEXT("bullet")
		),
		life_time(
			10
		),
		direction_,
		indeterminate::no
	),
	damage_(damage_)
{}

void
sanguis::server::entities::projectiles::simple_bullet::do_damage(
	with_health &e
)
{
	e.damage(
		damage_,
		damage::list(
			damage::piercing = damage::full
		)
	);

	expire();
}
