#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/create_swarm.hpp>
#include <sanguis/server/ai/sight_range.hpp>


sanguis::server::ai::create_function
sanguis::server::ai::create_swarm(
	sanguis::random_generator &_random_generator,
	sanguis::server::ai::sight_range const _sight_range
)
{
	// FIXME!
	return
		sanguis::server::ai::create_simple(
			_random_generator,
			_sight_range
		);
/*
		[
			_sight_range
		](
			sanguis::server::entities::with_ai &_entity
		)
		{
			return
				fcppt::make_unique_ptr<
					sanguis::server::ai::swarm
				>(
					_entity,
					_sight_range
				);
		};*/
}
