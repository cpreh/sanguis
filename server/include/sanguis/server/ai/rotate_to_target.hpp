#ifndef SANGUIS_SERVER_AI_ROTATE_TO_TARGET_HPP_INCLUDED
#define SANGUIS_SERVER_AI_ROTATE_TO_TARGET_HPP_INCLUDED

#include <sanguis/server/ai/target_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>

namespace sanguis::server::ai
{

void rotate_to_target(
    sanguis::server::entities::with_ai &, // NOLINT(google-runtime-references)
    sanguis::server::ai::target const &);

}

#endif
