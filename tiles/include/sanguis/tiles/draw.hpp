#ifndef SANGUIS_TILES_DRAW_HPP_INCLUDED
#define SANGUIS_TILES_DRAW_HPP_INCLUDED

#include <sanguis/creator/background_grid_fwd.hpp>
#include <sanguis/creator/min_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/sup_fwd.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection_ref.hpp>
#include <sanguis/tiles/log_fwd.hpp>
#include <sanguis/tiles/symbol.hpp>


namespace sanguis
{
namespace tiles
{

SANGUIS_TILES_SYMBOL
sanguis::tiles::cell_container
draw(
	sanguis::tiles::log const &,
	sanguis::creator::grid const &,
	sanguis::creator::background_grid const &,
	sanguis::tiles::collection_ref,
	sanguis::creator::min const &,
	sanguis::creator::sup const &
);

}
}

#endif
