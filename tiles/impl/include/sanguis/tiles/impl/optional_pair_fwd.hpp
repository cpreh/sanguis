#ifndef SANGUIS_TILES_IMPL_OPTIONAL_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_OPTIONAL_PAIR_FWD_HPP_INCLUDED

#include <sanguis/tiles/pair_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::tiles::impl
{

template<
	typename Tile
>
using
optional_pair
=
fcppt::optional::object<
	sanguis::tiles::pair<
		Tile
	>
>;

}

#endif
