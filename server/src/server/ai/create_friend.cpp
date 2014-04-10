#include <sanguis/server/ai/create_friend.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/friend.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/entities/spawn_owner_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::ai::create_function
sanguis::server::ai::create_friend(
	sanguis::server::ai::sight_range const _sight_range,
	sanguis::server::entities::spawn_owner const &_spawn_owner
)
{
	return
		[
			_sight_range,
			&_spawn_owner
		](
			sanguis::server::entities::with_ai &_entity
		)
		{
			return
				fcppt::make_unique_ptr<
					sanguis::server::ai::friend_
				>(
					_entity,
					_sight_range,
					_spawn_owner
				);
		};
}
