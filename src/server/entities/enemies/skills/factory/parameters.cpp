#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>


sanguis::server::entities::enemies::skills::factory::parameters::parameters(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	difficulty_(
		_difficulty
	)
{
}

sanguis::diff_clock const &
sanguis::server::entities::enemies::skills::factory::parameters::diff_clock() const
{
	return
		diff_clock_;
}

sanguis::random_generator &
sanguis::server::entities::enemies::skills::factory::parameters::random_generator() const
{
	return
		random_generator_;
}

sanguis::server::entities::enemies::difficulty const
sanguis::server::entities::enemies::skills::factory::parameters::difficulty() const
{
	return
		difficulty_;
}
