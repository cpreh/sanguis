#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/visitor.hpp>
#include <fcppt/variant/apply_unary.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::create(
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _type,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	return
		fcppt::variant::apply_unary(
			sanguis::server::weapons::factory::visitor(
				sanguis::server::weapons::factory::parameters(
					_random_generator,
					_type,
					_difficulty
				)
			),
			_type
		);
}
