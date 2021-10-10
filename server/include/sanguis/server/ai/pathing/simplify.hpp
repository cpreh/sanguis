#ifndef SANGUIS_SERVER_AI_PATHING_SIMPLIFY_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_SIMPLIFY_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>

namespace sanguis::server::ai::pathing
{

sanguis::server::ai::pathing::trail
simplify(sanguis::server::ai::pathing::trail const &, sanguis::creator::grid const &);

}

#endif
