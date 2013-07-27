#ifndef SANGUIS_CREATOR_BACKGROUND_GRID_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_BACKGROUND_GRID_FWD_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp>
#include <fcppt/container/grid/object_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::grid::object<
	sanguis::creator::background_tile,
	2u
>
background_grid;

}
}

#endif
