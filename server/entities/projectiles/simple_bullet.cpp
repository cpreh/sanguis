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
#include <sge/optional_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	server::environment::load_context_ptr const load_context,
	team::type const team_,
	space_unit const damage
)
:
	projectile(
		projectile_type::simple_bullet,
		load_context,
		team_,
		boost::assign::map_list_of
			(
				entities::property_type::health,
				entities::property(static_cast<space_unit>(1))
			)
			(
				entities::property_type::movement_speed,
				entities::property(static_cast<space_unit>(500))
			),
		load_context->entity_dim(
			SGE_TEXT("bullet")
		),
		static_cast<time_type>(10),
		indeterminate::no
	),
	damage(damage)
{}

void
sanguis::server::entities::projectiles::simple_bullet::do_damage(
	entity &e
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
