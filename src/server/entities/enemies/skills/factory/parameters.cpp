#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters.hpp>


sanguis::server::entities::enemies::skills::factory::parameters::parameters(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
:
	diff_clock_(
		_diff_clock
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

sanguis::server::entities::enemies::difficulty const
sanguis::server::entities::enemies::skills::factory::parameters::difficulty() const
{
	return
		difficulty_;
}
