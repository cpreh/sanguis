#include "rocket.hpp"
#include "aoe_damage.hpp"
#include "../property.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/fire.hpp"
#include "../../damage/full.hpp"
#include "../../environment/object.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/text.hpp>
#include <sge/optional_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::rocket::rocket(
	server::environment::object_ptr const env,
	pos_type const &center,
	space_unit const angle,
	team::type const team_,
	space_unit const damage,
	space_unit const aoe_
)
:
	aoe_projectile(
		aoe_projectile_type::rocket,
		env,
		center,
		angle,
		team_,
		boost::assign::map_list_of
			(
				entities::property_type::health,
				entities::property(static_cast<space_unit>(1))
			)
			(
				entities::property_type::movement_speed,
				entities::property(static_cast<space_unit>(300))
			),
		env->entity_dim(
			SGE_TEXT("rocket")
		),
		static_cast<time_type>(10),
		indeterminate::no,
		aoe_
	),
	damage(damage)
{}

void
sanguis::server::entities::projectiles::rocket::do_damage(
	entity &)
{
	die();
}

void sanguis::server::entities::projectiles::rocket::on_die()
{
	environment()->insert(
		auto_ptr(
			new aoe_damage(
				environment(),
				center(),
				team(),
				aoe(),
				damage,
				1,
				static_cast<time_type>(0.1),
				damage::list(
					damage::fire = damage::full
				)
			)
		)
	);
}
