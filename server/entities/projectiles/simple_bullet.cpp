#include "simple_bullet.hpp"
#include "../property.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/piercing.hpp"
#include "../../damage/full.hpp"
#include "../../environment/load_context.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/text.hpp>

sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	server::environment::load_context_ptr const load_context,
	team::type const team_,
	damage::unit const damage_,
	space_unit const direction_
)
:
	projectile(
		projectile_type::simple_bullet,
		load_context,
		team_,
		server::movement_speed(
			500
		),
		load_context->entity_dim(
			SGE_TEXT("bullet")
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
		damage,
		damage::list(
			damage::piercing = damage::full
		)
	);

	die();
}
