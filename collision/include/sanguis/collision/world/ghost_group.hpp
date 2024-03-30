#ifndef SANGUIS_COLLISION_WORLD_GHOST_GROUP_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_GROUP_HPP_INCLUDED

#include <sanguis/collision/world/ghost_group_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::collision::world
{

enum class ghost_group : std::uint8_t
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
