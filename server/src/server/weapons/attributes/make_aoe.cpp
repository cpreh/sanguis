#include <sanguis/weapon_attribute.hpp>
#include <sanguis/server/weapons/attributes/aoe.hpp>
#include <sanguis/server/weapons/attributes/make.hpp>
#include <sanguis/server/weapons/attributes/make_aoe.hpp>

sanguis::weapon_attribute sanguis::server::weapons::attributes::make_aoe(
    sanguis::server::weapons::attributes::aoe const &_aoe)
{
  return sanguis::server::weapons::attributes::make(sanguis::weapon_attribute_type::aoe, _aoe);
}
