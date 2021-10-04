#ifndef SANGUIS_SERVER_AI_PATHING_FIND_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_FIND_TARGET_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/ai/pathing/optional_trail.hpp>
#include <sanguis/server/ai/pathing/start_fwd.hpp>
#include <sanguis/server/ai/pathing/target_fwd.hpp>


namespace sanguis::server::ai::pathing
{

[[nodiscard]]
sanguis::server::ai::pathing::optional_trail
find_target(
	sanguis::creator::grid const &,
	sanguis::server::ai::pathing::start const &,
	sanguis::server::ai::pathing::target const &
);

}

#endif
