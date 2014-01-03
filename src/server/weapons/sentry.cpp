#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/create_function.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/optional_magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/sentry.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::sentry::sentry(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::magazine_size const _magazine_size,
	sanguis::server::weapons::create_function const &_sentry_weapon
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_random_generator,
		sanguis::weapon_type(
			sanguis::secondary_weapon_type::sentry
		),
		sanguis::server::weapons::accuracy(
			1.f
		),
		_range,
		sanguis::server::weapons::optional_magazine_size(
			_magazine_size
		),
		_base_cooldown,
		_cast_point,
		sanguis::server::weapons::optional_reload_time()
	),
	sentry_weapon_(
		_sentry_weapon
	)
{
}

sanguis::server::weapons::sentry::~sentry()
{
}

bool
sanguis::server::weapons::sentry::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	return
		_attack.environment().insert(
			fcppt::make_unique_ptr<
				sanguis::server::entities::friend_
			>(
				this->diff_clock(),
				this->random_generator(),
				sanguis::friend_type::sentry,
				_attack.environment().load_context(),
				sanguis::server::damage::no_armor(),
				sanguis::server::health(
					100.f
				),
				sanguis::server::entities::movement_speed(
					0.f
				),
				sanguis::server::ai::create_simple(
					sanguis::server::ai::sight_range(
						1000.f
					)
				),
				sentry_weapon_()
			),
			sanguis::server::entities::insert_parameters(
				sanguis::server::center(
					_attack.target().get()
				),
				_attack.angle()
			)
		).has_value();
}

sanguis::string_vector
sanguis::server::weapons::sentry::attributes() const
{
	// TODO:
	return
		sanguis::string_vector{};
}
