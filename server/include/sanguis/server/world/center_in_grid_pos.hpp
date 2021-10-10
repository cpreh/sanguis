#ifndef SANGUIS_SERVER_WORLD_CENTER_IN_GRID_POS_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CENTER_IN_GRID_POS_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>

namespace sanguis::server::world
{

bool center_in_grid_pos(sanguis::server::center const &, sanguis::creator::pos const &);

}

#endif
