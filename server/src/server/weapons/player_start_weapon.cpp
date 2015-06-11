#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/player_start_weapon.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::player_start_weapon(
	sanguis::random_generator &_random_generator
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::weapons::weapon
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::server::weapons::pistol
			>(
				_random_generator,
				sanguis::weapon_type(
					sanguis::primary_weapon_type::pistol
				),
				sanguis::server::weapons::pistol_parameters(
					sanguis::server::weapons::accuracy(
						0.93f
					),
					sanguis::server::weapons::backswing_time(
						sanguis::duration_second(
							1.0f / 8
						)
					),
					sanguis::server::weapons::damage(
						5.f
					),
					sanguis::server::weapons::cast_point(
						sanguis::duration_second(
							0.0f
						)
					),
					sanguis::server::weapons::magazine_size(
						12u
					),
					sanguis::server::weapons::reload_time(
						sanguis::duration_second(
							3.5f
						)
					),
					sanguis::server::weapons::range(
						1000.f
					)
				)
			)
		);
}
