#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/projectiles/collision_group.hpp>
#include <fcppt/assert/unreachable.hpp>

sanguis::collision::world::body_group
sanguis::server::entities::projectiles::collision_group(sanguis::server::team const _team)
{
  switch (_team)
  {
  case sanguis::server::team::players:
    return sanguis::collision::world::body_group::projectile_player;
  case sanguis::server::team::monsters:
    return sanguis::collision::world::body_group::projectile_enemy;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
