#ifndef SANGUIS_PERK_TYPE_HPP_INCLUDED
#define SANGUIS_PERK_TYPE_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp> // IWYU pragma: keep

namespace sanguis
{

enum class perk_type
{
  choleric,
  health,
  fire_damage,
  piercing_damage,
  ias,
  ims,
  irs,
  fcppt_maximum = irs
};

}

#endif
