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
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/damage/fire.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/insert_to_attack_result.hpp>
#include <sanguis/server/weapons/optional_magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/sentry.hpp>
#include <sanguis/server/weapons/sentry_parameters.hpp>
#include <sanguis/server/weapons/sentry_weapon.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::sentry::sentry(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::weapons::sentry_weapon const &_sentry_weapon,
	sanguis::server::weapons::sentry_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_random_generator,
		sanguis::weapon_type(
			sanguis::secondary_weapon_type::sentry
		),
		sanguis::server::weapons::accuracy(
			fcppt::literal<
				sanguis::server::weapons::accuracy::value_type
			>(
				1
			)
		),
		_parameters.range(),
		sanguis::server::weapons::optional_magazine_size(
			_parameters.magazine_size()
		),
		_parameters.base_cooldown(),
		_parameters.cast_point(),
		sanguis::server::weapons::optional_reload_time()
	),
	health_(
		_parameters.health()
	),
	sentry_weapon_(
		_sentry_weapon
	)
{
}

sanguis::server::weapons::sentry::~sentry()
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::sentry::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	return
		sanguis::server::weapons::insert_to_attack_result(
			_attack.environment().insert(
				fcppt::make_unique_ptr<
					sanguis::server::entities::friend_
				>(
					this->diff_clock(),
					this->random_generator(),
					sanguis::friend_type::sentry,
					_attack.environment().load_context(),
					sanguis::server::damage::armor(
						sanguis::server::damage::list(
							sanguis::server::damage::fire =
								sanguis::server::damage::unit(
									0.9f
								)
						)
					),
					health_,
					sanguis::server::entities::movement_speed(
						0.f
					),
					sanguis::server::ai::create_simple(
						sanguis::server::ai::sight_range(
							1000.f
						)
					),
					sentry_weapon_.get()()
				),
				sanguis::server::entities::insert_parameters(
					sanguis::server::center(
						_attack.target().get()
					),
					_attack.angle()
				)
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
