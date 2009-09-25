#include "melee.hpp"
#include "../property.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/normal.hpp"
#include "../../damage/full.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/container/map_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::melee::melee(
	team::type const team_,
	damage::unit const damage_
)
:
	projectile(
		projectile_type::melee,
		team_,
		server::movement_speed(
			0
		),
		dim_type(
			1,
			1
		),
		life_time(
			1
		), // short lifetime
		indeterminate::yes
	),
	damage_(damage_)
{}

void
sanguis::server::entities::projectiles::melee::do_damage(
	with_health &e
)
{
	e.damage(
		damage_,
		damage::list(
			damage::normal = damage::full
		)
	);

	die();
}
