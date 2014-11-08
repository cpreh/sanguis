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

bool
make_path(
	sanguis::server::ai::context &,
	sanguis::creator::pos
);

}
}
}

#endif
