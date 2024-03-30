#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/collision_group.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::collision::world::ghost_group sanguis::server::auras::collision_group(
    sanguis::server::team const _team, sanguis::server::auras::influence const _influence)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
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
    throw fcppt::enum_::make_invalid(_team);
  case sanguis::server::auras::influence::debuff:
    switch (_team)
    {
    case sanguis::server::team::players:
      return sanguis::collision::world::ghost_group::target_enemy;
    case sanguis::server::team::monsters:
      return sanguis::collision::world::ghost_group::target_player;
    }
    throw fcppt::enum_::make_invalid(_team);
  }

  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_influence);
}
