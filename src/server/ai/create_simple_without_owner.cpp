#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/create_simple_without_owner.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>


sanguis::server::ai::create_function const
sanguis::server::ai::create_simple_without_owner(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
{
	return
		sanguis::server::ai::create_simple(
			_diff_clock,
			_random_generator,
			sanguis::server::entities::auto_weak_link()
		);
}
