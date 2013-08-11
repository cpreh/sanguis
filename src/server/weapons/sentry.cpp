#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/ai/create_simple_without_owner.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/create_function.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/magazine_count.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/sentry.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::sentry::sentry(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::reload_time const _reload_time,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::create_function const &_sentry_weapon
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		sanguis::weapon_type(
			sanguis::secondary_weapon_type::sentry
		),
		_range,
		sanguis::server::weapons::magazine_size(
			1U
		),
		sanguis::server::weapons::magazine_count(
			1u
		),
		_base_cooldown,
		_cast_point,
		_reload_time
	),
	random_generator_(
		_random_generator
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
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::friend_
		>(
			this->diff_clock(),
			sanguis::friend_type::sentry,
			_attack.environment().load_context(),
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				100.f
			),
			sanguis::server::entities::movement_speed(
				0.f
			),
			sanguis::server::ai::create_simple_without_owner(
				this->diff_clock(),
				random_generator_
			),
			sentry_weapon_()
		),
		sanguis::server::entities::insert_parameters(
			sanguis::server::center(
				_attack.target().get()
			),
			_attack.angle()
		)
	);
}

sanguis::string_vector
sanguis::server::weapons::sentry::attributes() const
{
	// TODO:
	return
		sanguis::string_vector{};
}
