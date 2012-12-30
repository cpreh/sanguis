#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::ai::create_function const
sanguis::server::ai::create_simple(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::auto_weak_link const &_link
)
{
	return
		[
			&_diff_clock,
			&_random_generator,
			_link
		](
			sanguis::server::entities::with_ai &_entity
		)
		{
			return
				fcppt::make_unique_ptr<
					sanguis::server::ai::simple
				>(
					_diff_clock,
					_random_generator,
					_entity,
					_link
				);
		};
}
