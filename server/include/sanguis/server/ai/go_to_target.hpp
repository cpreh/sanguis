#ifndef SANGUIS_SERVER_AI_GO_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_GO_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/in_range.hpp>
#include <sanguis/server/ai/is_visible.hpp>
#include <sanguis/server/ai/speed_factor_fwd.hpp>
#include <sanguis/server/ai/target_fwd.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

bool
go_to_target(
	sanguis::server::ai::context &,
	sanguis::server::ai::in_range,
	sanguis::server::ai::is_visible,
	sanguis::server::ai::target,
	sanguis::server::ai::speed_factor
)
FCPPT_PP_WARN_UNUSED_RESULT;

}
}
}

#endif
