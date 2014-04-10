#ifndef SANGUIS_SERVER_AI_PATHING_FIND_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_FIND_TARGET_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/ai/pathing/start_fwd.hpp>
#include <sanguis/server/ai/pathing/target_fwd.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace pathing
{

sanguis::server::ai::pathing::trail
find_target(
	sanguis::creator::grid const &,
	sanguis::server::ai::pathing::start,
	sanguis::server::ai::pathing::target
);

}
}
}
}

#endif
