#include <sanguis/server/damage/armor_meta.hpp>
#include <sanguis/server/damage/armor_unit.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/wrapper.hpp>

sanguis::server::damage::wrapper::wrapper(sanguis::server::damage::type const _type) : type_(_type)
{
}

// NOLINTNEXTLINE(cppcoreguidelines-c-copy-assignment-signature,misc-unconventional-assign-operator)
sanguis::server::damage::meta
sanguis::server::damage::wrapper::operator=(sanguis::server::damage::unit const _unit) const
{
  return sanguis::server::damage::meta(type_, _unit);
}

// NOLINTNEXTLINE(cppcoreguidelines-c-copy-assignment-signature,misc-unconventional-assign-operator)
sanguis::server::damage::armor_meta
sanguis::server::damage::wrapper::operator=(sanguis::server::damage::armor_unit const _unit) const
{
  return sanguis::server::damage::armor_meta(type_, _unit);
}
