#include "grenade.hpp"
#include "aoe_damage.hpp"
#include "../property.hpp"
#include "../../default_dim.hpp"
#include "../../damage/list.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/piercing.hpp"
#include "../../damage/fire.hpp"
#include "../../collision/distance.hpp"
#include "../../../load/context.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/time/resolution.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/text.hpp>
#include <sge/optional_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::grenade::grenade(
	server::environment const &env,
	pos_type const &center,
	space_unit const angle,
	team::type const team_,
	space_unit const damage,
	space_unit const aoe_,
	pos_type const &dest_)
:
	aoe_projectile(
		aoe_projectile_type::grenade,
		env,
		center,
		angle,
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
					collision::distance(
						center,
						dest_
					)
				)
			),
		default_dim(
			env.load()().models(),
			SGE_TEXT("grenade")
		),
		static_cast<time_type>(2),
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
	entity &)
{}

void
sanguis::server::entities::projectiles::grenade::update(
	time_type const time,
	container &cont)
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
		time,
		cont
	);
}

void
sanguis::server::entities::projectiles::grenade::on_die()
{
	insert(
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
					damage::piercing = static_cast<damage::value_type>(0.5)
				)(
					damage::fire = static_cast<damage::value_type>(0.5)
				)
			)
		)
	);
}
