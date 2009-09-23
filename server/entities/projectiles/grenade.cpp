#include "grenade.hpp"
#include "aoe_damage.hpp"
#include "../property.hpp"
#include "../insert_parameters.hpp"
#include "../../damage/list.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/piercing.hpp"
#include "../../damage/fire.hpp"
#include "../../collision/distance.hpp"
#include "../../environment/object.hpp"
#include "../../environment/load_context.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/text.hpp>
#include <sge/optional_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::grenade::grenade(
	server::environment::load_context_ptr const load_context_,
	team::type const team_,
	space_unit const damage,
	space_unit const aoe_,
	pos_type const &dest_
)
:
	aoe_projectile(
		aoe_projectile_type::grenade,
		load_context_,
		team_,
		boost::assign::map_list_of
			(
				entities::property_type::health,
				entities::property(
					static_cast<space_unit>(1)
				)
			)
			(
				entities::property_type::movement_speed,
				entities::property(
					static_cast<space_unit>(100) // FIXME
					/*
					collision::distance(
						center,
						dest_
					)*/
				)
			),
		load_context_->entity_dim(
			SGE_TEXT("grenade")
		),
		life_time(
			2
		),
		indeterminate::no,
		aoe_
	),
	diff_clock_(),
	slowdown_time(
		sge::time::millisecond(
			100
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	damage(damage)
{}

void
sanguis::server::entities::projectiles::grenade::do_damage(
	entity &
)
{}

void
sanguis::server::entities::projectiles::grenade::update(
	time_type const time
)
{
	diff_clock_.update(
		time
	);

	entities::property &speed(
		property(
			property_type::movement_speed
		)
	);

	if(slowdown_time.update_b())
		speed.current(
			speed.current() * static_cast<space_unit>(0.9)
		);
	
	projectile::update(
		time
	);
}

void
sanguis::server::entities::projectiles::grenade::on_die()
{
	environment()->insert(
		auto_ptr(
			new aoe_damage(
				load_context(),
				team(),
				aoe(),
				damage,
				1,
				static_cast<time_type>(0.1),
				damage::list(
					damage::piercing = static_cast<damage::value_type>(0.5)
				)(
					damage::fire = static_cast<damage::value_type>(0.5)
				)
			)
		),
		insert_parameters(
			center(),
			angle(),
			angle()
		)
	);
}
