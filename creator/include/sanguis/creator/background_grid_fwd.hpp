#ifndef SANGUIS_CREATOR_BACKGROUND_GRID_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_BACKGROUND_GRID_FWD_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_grid_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
sanguis::creator::tile_grid<
	sanguis::creator::background_tile
>
background_grid;

}
}

#endif
