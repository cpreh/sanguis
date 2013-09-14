#include <sanguis/collision/aux_/world/group_pair.hpp>
#include <sanguis/collision/aux_/world/group_pair_vector.hpp>
#include <sanguis/collision/aux_/world/group_relation.hpp>
#include <sanguis/collision/world/group.hpp>


namespace
{

sanguis::collision::aux_::world::group_pair_vector const init{
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::enemy,
		sanguis::collision::world::group::projectile_player
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::pickup,
		sanguis::collision::world::group::player
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::player,
		sanguis::collision::world::group::projectile_enemy
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::enemy
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::player
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::pickup
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::projectile_enemy
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::projectile_player
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::sight_range,
		sanguis::collision::world::group::weapon_pickup
	),
	sanguis::collision::aux_::world::group_pair(
		sanguis::collision::world::group::weapon_pickup,
		sanguis::collision::world::group::weapon_pickup_sight
	)
};

}

sanguis::collision::aux_::world::group_pair_vector const &
sanguis::collision::aux_::world::group_relation()
{
	return
		init;
}
