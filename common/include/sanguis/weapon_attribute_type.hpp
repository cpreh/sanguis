#ifndef SANGUIS_WEAPON_ATTRIBUTE_TYPE_HPP_INCLUDED
#define SANGUIS_WEAPON_ATTRIBUTE_TYPE_HPP_INCLUDED

#include <sanguis/weapon_attribute_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{

enum class weapon_attribute_type : std::uint8_t
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
