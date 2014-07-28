#ifndef SANGUIS_CLIENT_LOAD_TILES_SORT_PAIR_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_SORT_PAIR_HPP_INCLUDED

#include <sanguis/client/load/tiles/pair.hpp>


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
sanguis::client::load::tiles::pair<
	Tile
> const
sort_pair(
	sanguis::client::load::tiles::pair<
		Tile
	> const _arg
)
{
	return
		_arg.first
		<
		_arg.second
		?
			_arg
		:
			sanguis::client::load::tiles::pair<
				Tile
			>(
				_arg.second,
				_arg.first
			)
		;
}

}
}
}
}

#endif
