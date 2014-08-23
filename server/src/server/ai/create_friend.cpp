#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/create_friend.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <sanguis/server/ai/tree/make_leaf.hpp>
#include <sanguis/server/entities/spawn_owner_fwd.hpp>


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
			sanguis::server::ai::context &_context
		)
		{
			// TODO:
			return
				sanguis::server::ai::tree::make_leaf<
					sanguis::server::ai::behavior::attack
				>(
					_context,
					_sight_range
				);
		};
}
