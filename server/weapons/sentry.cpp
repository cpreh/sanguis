#include "sentry.hpp"
#include "delayed_attack.hpp"
#include "../ai/create_simple.hpp"
#include "../damage/no_armor.hpp"
#include "../damage/list.hpp"
#include "../entities/friend.hpp"
#include "../entities/insert_parameters.hpp"
#include "../environment/object.hpp"
#include <fcppt/container/map_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::weapons::sentry::sentry(
	weapon_type::type const type_,
	weapons::base_cooldown const base_cooldown_,
	weapons::cast_point const cast_point_,
	weapons::reload_time const reload_time_,
	create_function const &sentry_weapon
)
:
	weapon(
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
	delayed_attack const &a
)
{
	a.environment()->insert(
		entities::auto_ptr(
			new entities::friend_(
				friend_type::sentry,
				a.environment()->load_context(),
				damage::no_armor(),
				entities::health_type(100),
				entities::movement_speed(0),
				ai::create_simple(),
				auto_ptr(
					sentry_weapon()
				)
			)
		),
		entities::insert_parameters(
			a.dest(),
			a.angle()
		)
	);
}
