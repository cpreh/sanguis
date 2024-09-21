#ifndef SANGUIS_COLLISION_WORLD_BODY_GROUP_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_GROUP_HPP_INCLUDED

#include <sanguis/collision/world/body_group_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis::collision::world
{

enum class body_group : std::uint8_t
{
  doodad,
  destructible,
  enemy,
  pickup,
  projectile_enemy,
  projectile_player,
  player,
  weapon_pickup
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sanguis::collision::world::body_group::weapon_pickup);

#endif
