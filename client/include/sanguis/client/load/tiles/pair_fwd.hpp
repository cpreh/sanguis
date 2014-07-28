#ifndef SANGUIS_CLIENT_LOAD_TILES_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_PAIR_FWD_HPP_INCLUDED

#include <fcppt/homogenous_pair_fwd.hpp>


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
pair
=
fcppt::homogenous_pair<
	Tile
>;

}
}
}
}

#endif
