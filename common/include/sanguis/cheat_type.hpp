#ifndef SANGUIS_CHEAT_TYPE_HPP_INCLUDED
#define SANGUIS_CHEAT_TYPE_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis
{

enum class cheat_type
{
  auras,
  exp,
  grenade,
  heal,
  kill,
  monster_spawner,
  perks,
  rocket_launcher,
  sentry,
  shotgun,
  spider,
  fcppt_maximum = spider
};

}

#endif
