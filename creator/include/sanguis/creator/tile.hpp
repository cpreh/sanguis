#ifndef SANGUIS_CREATOR_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_TILE_HPP_INCLUDED

#include <sanguis/creator/tile_fwd.hpp>


namespace sanguis
{
namespace creator
{

enum class tile
{
	nothing,
	stairs,
	space_door_closed_v,
	space_door_open_v,
	space_door_closed_h,
	space_door_open_h,
	spawner,
	grave1,
	grave2,
	grave3,
	grave4,
	grave5,
	hedge,
	concrete_wall,
	fcppt_maximum = concrete_wall
};

}
}

#endif
