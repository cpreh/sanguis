#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/create_swarm.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/swarm.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::ai::create_function
sanguis::server::ai::create_swarm(
	sanguis::server::ai::sight_range const _sight_range
)
{
	return
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
		};
}
