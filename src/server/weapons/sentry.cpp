#include <sanguis/server/weapons/sentry.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/ai/create_simple_without_owner.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::weapons::sentry::sentry(
	sanguis::diff_clock const &_diff_clock,
	weapon_type::type const _type,
	weapons::base_cooldown const _base_cooldown,
	weapons::cast_point const _cast_point,
	weapons::reload_time const _reload_time,
	create_function const &_sentry_weapon
)
:
	weapon(
		_diff_clock,
		_type,
		weapons::range(
			20
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
				this->diff_clock(),
				friend_type::sentry,
				_attack.environment().load_context(),
				damage::no_armor(),
				server::health(100),
				entities::movement_speed(0),
				ai::create_simple_without_owner(
					this->diff_clock()
				),
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
