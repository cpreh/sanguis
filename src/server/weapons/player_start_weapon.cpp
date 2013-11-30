#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/player_start_weapon.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::player_start_weapon(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::weapons::pistol
		>(
			_diff_clock,
			_random_generator,
			sanguis::weapon_type(
				sanguis::primary_weapon_type::pistol
			),
			sanguis::server::weapons::accuracy(
				0.8f
			),
			sanguis::server::weapons::base_cooldown(
				sanguis::duration_second(
					0.5f
				)
			),
			sanguis::server::weapons::damage(
				5.f
			),
			sanguis::server::weapons::cast_point(
				sanguis::duration_second(
					0.2f
				)
			),
			sanguis::server::weapons::magazine_size(
				18u
			),
			sanguis::server::weapons::reload_time(
				sanguis::duration_second(
					2.f
				)
			),
			sanguis::server::weapons::range(
				1000.f
			)
		);
}
