#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/visitor.hpp>
#include <fcppt/variant/apply_unary.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::create(
	sanguis::diff_clock const  &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _type
)
{
	return
		fcppt::variant::apply_unary(
			sanguis::server::weapons::factory::visitor(
				sanguis::server::weapons::factory::parameters(
					_diff_clock,
					_random_generator,
					_type
				)
			),
			_type
		);
}
