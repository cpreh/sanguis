#ifndef SANGUIS_COLLISION_IMPL_WORLD_BODY_GHOST_GROUP_RELATION_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_BODY_GHOST_GROUP_RELATION_HPP_INCLUDED

#include <sanguis/collision/impl/world/body_ghost_group_pair.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <fcppt/mpl/list/object.hpp>

namespace sanguis::collision::impl::world
{

using body_ghost_group_relation = fcppt::mpl::list::object<
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::destructible,
        sanguis::collision::world::ghost_group::player_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::doodad,
        sanguis::collision::world::ghost_group::player_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::enemy,
        sanguis::collision::world::ghost_group::player_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::player,
        sanguis::collision::world::ghost_group::player_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::pickup,
        sanguis::collision::world::ghost_group::player_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::projectile_enemy,
        sanguis::collision::world::ghost_group::player_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::projectile_player,
        sanguis::collision::world::ghost_group::player_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::weapon_pickup,
        sanguis::collision::world::ghost_group::player_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::weapon_pickup,
        sanguis::collision::world::ghost_group::weapon_pickup_sight>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::player,
        sanguis::collision::world::ghost_group::enemy_aggro>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::player,
        sanguis::collision::world::ghost_group::target_player>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::enemy,
        sanguis::collision::world::ghost_group::target_enemy>,
    sanguis::collision::impl::world::body_ghost_group_pair<
        sanguis::collision::world::body_group::destructible,
        sanguis::collision::world::ghost_group::target_enemy>>;

}

#endif
