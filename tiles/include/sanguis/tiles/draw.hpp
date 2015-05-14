#ifndef SANGUIS_TILES_DRAW_HPP_INCLUDED
#define SANGUIS_TILES_DRAW_HPP_INCLUDED

#include <sanguis/creator/background_grid_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection_fwd.hpp>
#include <sanguis/tiles/lower_bound.hpp>
#include <sanguis/tiles/symbol.hpp>
#include <sanguis/tiles/upper_bound.hpp>


namespace sanguis
{
namespace tiles
{

SANGUIS_TILES_SYMBOL
sanguis::tiles::cell_container
draw(
	sanguis::creator::grid const &,
	sanguis::creator::background_grid const &,
	sanguis::tiles::collection &,
	sanguis::tiles::lower_bound,
	sanguis::tiles::upper_bound
);

}
}

#endif
