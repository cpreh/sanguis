#ifndef SANGUIS_SERVER_AI_MOVE_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_MOVE_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/optional_angle_fwd.hpp>
#include <sanguis/server/ai/speed_factor_fwd.hpp>
#include <sanguis/server/ai/target_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

void
move_to_target(
	sanguis::server::entities::with_ai &, // NOLINT(google-runtime-references)
	sanguis::server::optional_angle,
	sanguis::server::ai::target const &,
	sanguis::server::ai::speed_factor
);

}
}
}

#endif
