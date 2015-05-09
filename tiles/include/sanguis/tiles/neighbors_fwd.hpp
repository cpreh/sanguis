#ifndef SANGUIS_TILES_NEIGHBORS_FWD_HPP_INCLUDED
#define SANGUIS_TILES_NEIGHBORS_FWD_HPP_INCLUDED

#include <sanguis/tiles/direction_fwd.hpp>
#include <fcppt/container/enum_array_fwd.hpp>


namespace sanguis
{
namespace tiles
{

template<
	typename Tile
>
using
neighbors
=
fcppt::container::enum_array<
	sanguis::tiles::direction,
	Tile
>;

}
}

#endif
