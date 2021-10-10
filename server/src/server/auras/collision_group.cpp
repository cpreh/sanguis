#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/collision_group.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <fcppt/assert/unreachable.hpp>

sanguis::collision::world::ghost_group sanguis::server::auras::collision_group(
    sanguis::server::team const _team, sanguis::server::auras::influence const _influence)
{
  switch (_influence)
  {
  case sanguis::server::auras::influence::buff:
    switch (_team)
    {
    case sanguis::server::team::players:
      return sanguis::collision::world::ghost_group::target_player;
    case sanguis::server::team::monsters:
      return sanguis::collision::world::ghost_group::target_enemy;
    }
    break;
  case sanguis::server::auras::influence::debuff:
    switch (_team)
    {
    case sanguis::server::team::players:
      return sanguis::collision::world::ghost_group::target_enemy;
    case sanguis::server::team::monsters:
      return sanguis::collision::world::ghost_group::target_player;
    }
    break;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
