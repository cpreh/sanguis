#include "sentry.hpp"
#include "delayed_attack.hpp"
#include "../ai/simple.hpp"
#include "../damage/no_armor.hpp"
#include "../damage/list.hpp"
#include "../entities/friend.hpp"
#include "../entities/property.hpp"
#include <sge/container/map_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::weapons::sentry::sentry(
	server::environment const &env,
	weapon_type::type const type_,
	time_type const base_cooldown,
	time_type const cast_point,
	time_type const reload_time,
	create_function const &sentry_weapon)
:
	weapon(
		env,
		type_,
		1000, // FIXME
		1, // magazine size
		1, // number of magazine at start
		base_cooldown,
		cast_point,
		reload_time
	),
	sentry_weapon(sentry_weapon)
{}

void
sanguis::server::weapons::sentry::do_attack(
	delayed_attack const &a)
{
	insert(
		entities::auto_ptr(
			new entities::friend_(
				friend_type::sentry,
				environment(),
				damage::no_armor(),
				a.dest(),
				a.angle(),
				a.angle(), // direction
				a.team(),
				boost::assign::map_list_of
				(
					entities::property_type::health,
					entities::property(
						static_cast<space_unit>(9)
					)
				),
				ai::auto_ptr(
					new ai::simple()
				),
				auto_ptr(
					sentry_weapon()
				)
			)
		)
	);
}
