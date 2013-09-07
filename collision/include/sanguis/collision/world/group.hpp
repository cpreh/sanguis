#ifndef SANGUIS_COLLISION_WORLD_GROUP_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GROUP_HPP_INCLUDED

#include <sanguis/collision/world/group_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

enum class group
{
	enemy,
	pickup,
	projectile_enemy,
	projectile_player,
	player,
	sight_range,
	weapon_pickup,
	weapon_pickup_sight,
	fcppt_maximum = weapon_pickup_sight
};

}
}
}

#endif
