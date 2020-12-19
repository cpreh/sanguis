#ifndef SANGUIS_SERVER_AI_GO_CLOSE_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_GO_CLOSE_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/speed_factor_fwd.hpp>
#include <sanguis/server/ai/target_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

[[nodiscard]]
bool
go_close_to_target(
	sanguis::server::ai::context &, // NOLINT(google-runtime-references)
	sanguis::server::ai::target const &,
	sanguis::server::ai::speed_factor
);

}
}
}

#endif
