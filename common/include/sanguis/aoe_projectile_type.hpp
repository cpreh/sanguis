#ifndef SANGUIS_AOE_PROJECTILE_TYPE_HPP_INCLUDED
#define SANGUIS_AOE_PROJECTILE_TYPE_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis
{

enum class aoe_projectile_type
{
  rocket,
  grenade,
  fcppt_maximum = grenade
};

}

#endif
