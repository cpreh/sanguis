#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/player_start_weapon.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::player_start_weapon(
	sanguis::random_generator &_random_generator
)
{
	return
		sanguis::server::weapons::create(
			_random_generator,
			sanguis::weapon_type{
				sanguis::primary_weapon_type::pistol
			},
			sanguis::server::entities::enemies::difficulty{
				1.f
			}
		);
}
