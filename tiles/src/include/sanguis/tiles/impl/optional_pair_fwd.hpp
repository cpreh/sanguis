#ifndef SANGUIS_TILES_IMPL_OPTIONAL_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_OPTIONAL_PAIR_FWD_HPP_INCLUDED

#include <sanguis/tiles/pair_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

template<
	typename Tile
>
using
optional_pair
=
fcppt::optional<
	sanguis::tiles::pair<
		Tile
	>
>;

}
}
}

#endif
