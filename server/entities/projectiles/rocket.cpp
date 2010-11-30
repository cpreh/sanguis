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
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::projectiles::rocket::rocket(
	server::environment::load_context_ptr const _load_context,
	team::type const _team,
	damage::unit const _damage,
	space_unit const _aoe,
	space_unit const _angle
)
:
	aoe_projectile(
		aoe_projectile_type::rocket,
		_team,
		entities::movement_speed(300),
		_load_context->entity_dim(
			FCPPT_TEXT("rocket")
		),
		life_time(
			10
		),
		indeterminate::no,
		_aoe,
		_angle
	),
	damage_(
		_damage
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
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				aoe_damage
			>(
				team(),
				aoe(),
				damage_,
				1u,
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
