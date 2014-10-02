#ifndef SANGUIS_COLLISION_WORLD_BODY_GROUP_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_GROUP_HPP_INCLUDED

#include <sanguis/collision/world/body_group_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

enum class body_group
{
	enemy,
	pickup,
	projectile_enemy,
	projectile_player,
	player,
	weapon_pickup,
	fcppt_maximum = weapon_pickup
};

}
}
}

#endif
