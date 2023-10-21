#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/server/weapons/attributes/health.hpp>
#include <sanguis/server/weapons/attributes/make.hpp>
#include <sanguis/server/weapons/attributes/make_health.hpp>

sanguis::weapon_attribute sanguis::server::weapons::attributes::make_health(
    sanguis::server::weapons::attributes::health const &_health)
{
  return sanguis::server::weapons::attributes::make(
      sanguis::weapon_attribute_type::health, _health);
}
