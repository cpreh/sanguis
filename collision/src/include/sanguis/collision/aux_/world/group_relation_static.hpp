#ifndef SANGUIS_COLLISION_AUX__WORLD_GROUP_RELATION_STATIC_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_GROUP_RELATION_STATIC_HPP_INCLUDED

#include <sanguis/collision/aux_/world/group_pair_static.hpp>
#include <sanguis/collision/world/group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{

typedef
boost::mpl::map<
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::enemy,
		sanguis::collision::world::group::projectile_player
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::pickup,
		sanguis::collision::world::group::player
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::player,
		sanguis::collision::world::group::projectile_enemy
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::enemy
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::player
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::pickup
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::projectile_enemy
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::projectile_player
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::weapon_pickup
	>,
	sanguis::collision::aux_::world::group_pair_static<
		sanguis::collision::world::group::weapon_pickup,
		sanguis::collision::world::group::weapon_pickup_sight
	>
>
group_relation_static;

}
}
}
}

#endif
