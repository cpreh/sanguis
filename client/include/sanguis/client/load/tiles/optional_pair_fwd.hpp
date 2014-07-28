#ifndef SANGUIS_CLIENT_LOAD_TILES_OPTIONAL_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_OPTIONAL_PAIR_FWD_HPP_INCLUDED

#include <sanguis/client/load/tiles/pair_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

template<
	typename Tile
>
using
optional_pair
=
fcppt::optional<
	sanguis::client::load::tiles::pair<
		Tile
	>
>;

}
}
}
}

#endif
