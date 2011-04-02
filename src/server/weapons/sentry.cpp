#include "sentry.hpp"
#include "delayed_attack.hpp"
#include "../ai/create_simple.hpp"
#include "../damage/no_armor.hpp"
#include "../damage/list.hpp"
#include "../entities/friend.hpp"
#include "../entities/insert_parameters.hpp"
#include "../environment/object.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::weapons::sentry::sentry(
	weapon_type::type const _type,
	weapons::base_cooldown const _base_cooldown,
	weapons::cast_point const _cast_point,
	weapons::reload_time const _reload_time,
	create_function const &_sentry_weapon
)
:
	weapon(
		_type,
		weapons::range(
			1000
		), // FIXME
		weapons::magazine_size(
			1
		),
		weapons::magazine_count(
			1
		),
		_base_cooldown,
		_cast_point,
		_reload_time
	),
	sentry_weapon_(
		_sentry_weapon
	)
{
}

sanguis::server::weapons::sentry::~sentry()
{
}

void
sanguis::server::weapons::sentry::do_attack(
	delayed_attack const &_attack
)
{
	_attack.environment().insert(
		entities::unique_ptr(
			new entities::friend_(
//			fcppt::make_unique_ptr<
//				entities::friend_
//			>(
				friend_type::sentry,
				_attack.environment().load_context(),
				damage::no_armor(),
				server::health(100),
				entities::movement_speed(0),
				ai::create_simple(),
				weapons::unique_ptr(
					sentry_weapon_()
				)
			)
		),
		entities::insert_parameters(
			server::center(
				_attack.dest()
			),
			_attack.angle()
		)
	);
}
