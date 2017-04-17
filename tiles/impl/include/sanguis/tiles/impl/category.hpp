#ifndef SANGUIS_TILES_IMPL_CATEGORY_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_CATEGORY_HPP_INCLUDED

#include <sanguis/creator/enable_if_tile.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

template<
	typename Tile
>
sanguis::creator::enable_if_tile<
	Tile,
	fcppt::string
>
category();

}
}
}

#endif
