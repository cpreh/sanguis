#ifndef SANGUIS_SERVER_COLLISION_GROUP_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GROUP_HPP_INCLUDED

namespace sanguis
{
namespace server
{
namespace collision
{

namespace group
{
enum type {
	aggro_aura,
	enemy,
	pickup,	
	projectile_enemy,
	projectile_player,
	player,
	sight_range,
	size
};
}

}
}
}

#endif
