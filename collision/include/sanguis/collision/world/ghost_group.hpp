#ifndef SANGUIS_COLLISION_WORLD_GHOST_GROUP_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_GROUP_HPP_INCLUDED

#include <sanguis/collision/world/ghost_group_fwd.hpp>


namespace sanguis::collision::world
{

enum class ghost_group
{
	enemy_aggro,
	player_sight,
	target_enemy,
	target_player,
	weapon_pickup_sight,
	fcppt_maximum = weapon_pickup_sight
};

}

#endif
