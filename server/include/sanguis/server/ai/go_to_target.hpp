#ifndef SANGUIS_SERVER_AI_GO_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_GO_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/in_range.hpp>
#include <sanguis/server/ai/is_visible.hpp>
#include <sanguis/server/ai/speed_factor_fwd.hpp>
#include <sanguis/server/ai/target_fwd.hpp>

namespace sanguis::server::ai
{

[[nodiscard]] bool go_to_target(
    sanguis::server::ai::context &, // NOLINT(google-runtime-references)
    sanguis::server::ai::in_range,
    sanguis::server::ai::is_visible,
    sanguis::server::ai::target const &,
    sanguis::server::ai::speed_factor);

}

#endif
