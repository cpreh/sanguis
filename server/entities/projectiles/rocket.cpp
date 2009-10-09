#include "rocket.hpp"
#include "aoe_damage.hpp"
#include "../insert_parameters_pos.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/fire.hpp"
#include "../../damage/full.hpp"
#include "../../environment/object.hpp"
#include "../../environment/load_context.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/text.hpp>

sanguis::server::entities::projectiles::rocket::rocket(
	server::environment::load_context_ptr const load_context_,
	team::type const team_,
	damage::unit const damage_,
	space_unit const aoe_,
	space_unit const angle_
)
:
	aoe_projectile(
		aoe_projectile_type::rocket,
		team_,
		entities::movement_speed(300),
		load_context_->entity_dim(
			SGE_TEXT("rocket")
		),
		life_time(
			10
		),
		indeterminate::no,
		aoe_,
		angle_
	),
	damage_(
		damage_
	)
{}

void
sanguis::server::entities::projectiles::rocket::do_damage(
	with_health &
)
{
	expire();
}

void
sanguis::server::entities::projectiles::rocket::on_die()
{
	environment()->insert(
		auto_ptr(
			new aoe_damage(
				team(),
				aoe(),
				damage_,
				1,
				static_cast<time_type>(0.1),
				damage::list(
					damage::fire = damage::full
				)
			)
		),
		insert_parameters_pos(
			center()
		)
	);
}
