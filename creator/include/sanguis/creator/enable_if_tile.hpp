#ifndef SANGUIS_CREATOR_ENABLE_IF_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_ENABLE_IF_TILE_HPP_INCLUDED

#include <sanguis/creator/is_tile.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{

template<
	typename Tile,
	typename Result
>
using
enable_if_tile
=
std::enable_if_t<
	sanguis::creator::is_tile<
		Tile
	>::value,
	Result
>;

}
}

#endif
