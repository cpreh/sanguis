#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/projectiles/collision_group.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::collision::world::body_group
sanguis::server::entities::projectiles::collision_group(sanguis::server::team const _team)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_team)
  {
  case sanguis::server::team::players:
    return sanguis::collision::world::body_group::projectile_player;
  case sanguis::server::team::monsters:
    return sanguis::collision::world::body_group::projectile_enemy;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_team);
}
