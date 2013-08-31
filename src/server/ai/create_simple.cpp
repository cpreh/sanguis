#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::ai::create_function const
sanguis::server::ai::create_simple(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
{
	return
		[](
			sanguis::server::entities::with_ai &_entity
		)
		{
			return
				fcppt::make_unique_ptr<
					sanguis::server::ai::simple
				>(
					_entity
				);
		};
}
