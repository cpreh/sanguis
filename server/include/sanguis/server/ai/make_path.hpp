#ifndef SANGUIS_SERVER_AI_MAKE_PATH_HPP_INCLUDED
#define SANGUIS_SERVER_AI_MAKE_PATH_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/ai/context_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

[[nodiscard]]
bool
make_path(
	sanguis::server::ai::context &, // NOLINT(google-runtime-references)
	sanguis::creator::pos const &
);

}
}
}

#endif
