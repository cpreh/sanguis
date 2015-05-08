#ifndef SANGUIS_TILES_IMPL_INSTANTIATE_TILE_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_INSTANTIATE_TILE_HPP_INCLUDED

#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/tile.hpp>


#define SANGUIS_TILES_IMPL_INSTANTIATE_TILE(\
	macro\
)\
macro(\
	sanguis::creator::tile\
);\
macro( \
	sanguis::creator::background_tile\
)

#endif
