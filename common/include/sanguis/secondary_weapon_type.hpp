#ifndef SANGUIS_SECONDARY_WEAPON_TYPE_HPP_INCLUDED
#define SANGUIS_SECONDARY_WEAPON_TYPE_HPP_INCLUDED

#include <sanguis/secondary_weapon_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis
{

enum class secondary_weapon_type
{
  grenade,
  sentry,
  spider,
  fcppt_maximum = spider
};

}

#endif
