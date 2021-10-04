#ifndef SANGUIS_SERVER_AI_PATHING_POSITIONS_ARE_CLOSE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_POSITIONS_ARE_CLOSE_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>


namespace sanguis::server::ai::pathing
{

bool
positions_are_close(
	sanguis::creator::pos const &,
	sanguis::creator::pos const &
);

}

#endif
