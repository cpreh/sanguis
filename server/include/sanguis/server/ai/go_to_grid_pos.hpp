#ifndef SANGUIS_SERVER_AI_GO_TO_GRID_POS_HPP_INCLUDED
#define SANGUIS_SERVER_AI_GO_TO_GRID_POS_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/speed_factor_fwd.hpp>
#include <sanguis/server/ai/status.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

sanguis::server::ai::status
go_to_grid_pos(
	sanguis::server::ai::context &,
	sanguis::server::ai::speed_factor
);

}
}
}

#endif