#ifndef SANGUIS_CREATOR_BACKGROUND_GRID_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_BACKGROUND_GRID_FWD_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_grid_fwd.hpp>


namespace sanguis::creator
{

using
background_grid
=
sanguis::creator::tile_grid<
	sanguis::creator::background_tile
>;

}

#endif
