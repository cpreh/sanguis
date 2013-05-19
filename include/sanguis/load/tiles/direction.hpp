#ifndef SANGUIS_LOAD_TILES_DIRECTION_HPP_INCLUDED
#define SANGUIS_LOAD_TILES_DIRECTION_HPP_INCLUDED

#include <sanguis/load/tiles/direction_fwd.hpp>


namespace sanguis
{
namespace load
{
namespace tiles
{

enum class direction
{
	north,
	west,
	east,
	south,
	fcppt_maximum = south
};

}
}
}

#endif
