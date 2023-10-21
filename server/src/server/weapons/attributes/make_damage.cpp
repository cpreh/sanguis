#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/server/weapons/attributes/damage.hpp>
#include <sanguis/server/weapons/attributes/make.hpp>
#include <sanguis/server/weapons/attributes/make_damage.hpp>

sanguis::weapon_attribute sanguis::server::weapons::attributes::make_damage(
    sanguis::server::weapons::attributes::damage const &_damage)
{
  return sanguis::server::weapons::attributes::make(
      sanguis::weapon_attribute_type::damage, _damage);
}
