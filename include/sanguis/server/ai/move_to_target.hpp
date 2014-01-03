#ifndef SANGUIS_SERVER_AI_MOVE_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_MOVE_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/optional_angle_fwd.hpp>
#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

void
move_to_target(
	sanguis::server::entities::with_ai &,
	sanguis::server::optional_angle,
	sanguis::server::center,
	sanguis::server::ai::is_patrolling
);

}
}
}

#endif
