#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/parameters.hpp>


sanguis::server::world::parameters::parameters(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::world::context &_context,
	sanguis::server::environment::load_context &_load_context
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	context_(
		_context
	),
	load_context_(
		_load_context
	)
{
}

sanguis::diff_clock const &
sanguis::server::world::parameters::diff_clock() const
{
	return
		diff_clock_;
}

sanguis::random_generator &
sanguis::server::world::parameters::random_generator() const
{
	return
		random_generator_;
}

sanguis::server::world::context &
sanguis::server::world::parameters::context() const
{
	return
		context_;
}

sanguis::server::environment::load_context &
sanguis::server::world::parameters::load_context() const
{
	return
		load_context_;
}
