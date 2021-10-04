#ifndef SANGUIS_TILES_DIRECTION_HPP_INCLUDED
#define SANGUIS_TILES_DIRECTION_HPP_INCLUDED

#include <sanguis/tiles/direction_fwd.hpp>


namespace sanguis::tiles
{

enum class direction
{
	north_west,
	north_east,
	south_west,
	south_east,
	fcppt_maximum = south_east
};

}

#endif
