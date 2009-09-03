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
	weapons::base_cooldown const base_cooldown_,
	weapons::cast_point const cast_point_,
	weapons::reload_time const reload_time_,
	create_function const &sentry_weapon
)
:
	weapon(
		env,
		type_,
		weapons::range(
			1000
		), // FIXME
		weapons::magazine_size(
			1
		),
		weapons::magazine_count(
			1
		),
		base_cooldown_,
		cast_point_,
		reload_time_
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
						static_cast<space_unit>(100)
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
