#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/primary.hpp>
#include <sanguis/server/weapons/factory/secondary.hpp>
#include <fcppt/variant/match.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::create(
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _type,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	sanguis::server::weapons::factory::parameters const parameters(
		_random_generator,
		_type,
		_difficulty
	);

	return
		fcppt::variant::match(
			_type,
			[
				&parameters
			](
				sanguis::primary_weapon_type const _primary
			)
			{
				return
					sanguis::server::weapons::factory::primary(
						_primary,
						parameters
					);
			},
			[
				&parameters
			](
				sanguis::secondary_weapon_type const _secondary
			)
			{
				return
					sanguis::server::weapons::factory::secondary(
						_secondary,
						parameters
					);
			}
		);
}
