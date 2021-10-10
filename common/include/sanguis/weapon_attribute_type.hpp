#ifndef SANGUIS_WEAPON_ATTRIBUTE_TYPE_HPP_INCLUDED
#define SANGUIS_WEAPON_ATTRIBUTE_TYPE_HPP_INCLUDED

namespace sanguis
{

enum class weapon_attribute_type
{
  accuracy,
  aoe,
  damage,
  health,
  shells,
  spread_radius,
  fcppt_maximum = spread_radius
};

}

#endif
