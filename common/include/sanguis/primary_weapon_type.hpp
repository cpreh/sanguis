#ifndef SANGUIS_PRIMARY_WEAPON_TYPE_HPP_INCLUDED
#define SANGUIS_PRIMARY_WEAPON_TYPE_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis
{

// NOLINTNEXTLINE(performance-enum-size)
enum class primary_weapon_type
{
  melee,
  pistol,
  dual_pistols,
  shotgun,
  rocket_launcher,
  fcppt_maximum = rocket_launcher
};

}

#endif
