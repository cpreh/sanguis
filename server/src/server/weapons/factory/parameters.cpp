#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>


sanguis::server::weapons::factory::parameters::parameters(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _weapon_type,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	weapon_type_(
		_weapon_type
	),
	difficulty_(
		_difficulty
	)
{
}

sanguis::diff_clock const &
sanguis::server::weapons::factory::parameters::diff_clock() const
{
	return
		diff_clock_;
}

sanguis::random_generator &
sanguis::server::weapons::factory::parameters::random_generator() const
{
	return
		random_generator_;
}

sanguis::weapon_type const
sanguis::server::weapons::factory::parameters::weapon_type() const
{
	return
		weapon_type_;
}

sanguis::server::entities::enemies::difficulty const
sanguis::server::weapons::factory::parameters::difficulty() const
{
	return
		difficulty_;
}
