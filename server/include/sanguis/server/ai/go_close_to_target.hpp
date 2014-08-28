#ifndef SANGUIS_SERVER_AI_GO_CLOSE_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_GO_CLOSE_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/ai/target_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

void
go_close_to_target(
	sanguis::server::ai::context &,
	sanguis::server::ai::target,
	sanguis::server::ai::is_patrolling
);

}
}
}

#endif
