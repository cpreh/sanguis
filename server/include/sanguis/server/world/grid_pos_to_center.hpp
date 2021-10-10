#ifndef SANGUIS_SERVER_WORLD_GRID_POS_TO_CENTER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_GRID_POS_TO_CENTER_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>

namespace sanguis::server::world
{

sanguis::server::center grid_pos_to_center(sanguis::creator::pos const &);

}

#endif
