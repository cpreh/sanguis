#ifndef SANGUIS_CREATOR_AUX__GENERATE_MAZE_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__GENERATE_MAZE_HPP_INCLUDED

#include <sanguis/creator/aux_/randgen.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/tile_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace aux_
{

sanguis::creator::grid
generate_maze(
	sanguis::creator::grid::dim const &,
	unsigned const,
	unsigned const,
	sanguis::creator::tile const,
	sanguis::creator::tile const,
	sanguis::creator::aux_::randgen &
);

}
}
}

#endif
