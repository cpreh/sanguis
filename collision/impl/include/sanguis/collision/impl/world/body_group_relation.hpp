#ifndef SANGUIS_COLLISION_IMPL_WORLD_BODY_GROUP_RELATION_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_BODY_GROUP_RELATION_HPP_INCLUDED

#include <sanguis/collision/impl/world/body_group_pair.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <fcppt/mpl/map/object.hpp>

namespace sanguis::collision::impl::world
{

using body_group_relation = fcppt::mpl::map::object<
    sanguis::collision::impl::world::body_group_pair<
        sanguis::collision::world::body_group::enemy,
        sanguis::collision::world::body_group::projectile_player>,
    sanguis::collision::impl::world::body_group_pair<
        sanguis::collision::world::body_group::destructible,
        sanguis::collision::world::body_group::projectile_player>,
    sanguis::collision::impl::world::body_group_pair<
        sanguis::collision::world::body_group::pickup,
        sanguis::collision::world::body_group::player>,
    sanguis::collision::impl::world::body_group_pair<
        sanguis::collision::world::body_group::player,
        sanguis::collision::world::body_group::projectile_enemy>>;

}

#endif
