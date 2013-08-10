#ifndef SANGUIS_SERVER_COLLISION_GROUP_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GROUP_HPP_INCLUDED

#include <sanguis/server/collision/group_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
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
