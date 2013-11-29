#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::ai::create_function
sanguis::server::ai::create_simple(
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
					sanguis::server::ai::simple
				>(
					_entity,
					_sight_range
				);
		};
}
