#ifndef SANGUIS_SERVER_AI_ROTATE_AND_MOVE_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ROTATE_AND_MOVE_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/ai/target_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

void
rotate_and_move_to_target(
	sanguis::server::entities::with_ai &,
	sanguis::server::ai::target,
	sanguis::server::ai::is_patrolling
);

}
}
}

#endif
