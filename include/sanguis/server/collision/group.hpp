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
	obstacle,
	pickup,
	projectile_enemy,
	projectile_player,
	player,
	sight_range,
	fcppt_maximum = sight_range
};

}
}
}

#endif
