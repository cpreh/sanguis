#ifndef SANGUIS_TILES_IMPL_NEIGHBORS_FWD_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_NEIGHBORS_FWD_HPP_INCLUDED

#include <sanguis/tiles/direction_fwd.hpp>
#include <fcppt/enum/array_fwd.hpp>


namespace sanguis::tiles::impl
{

template<
	typename Tile
>
using
neighbors
=
fcppt::enum_::array<
	sanguis::tiles::direction,
	Tile
>;

}

#endif
