#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sanguis::load::aoe_projectile_name(sanguis::aoe_projectile_type const _type)
{
#define SANGUIS_LOAD_AOE_PROJECTILE_NAME_CASE(name) \
  case sanguis::aoe_projectile_type::name: \
    return FCPPT_TEXT(#name)

  switch (_type)
  {
    SANGUIS_LOAD_AOE_PROJECTILE_NAME_CASE(grenade);
    SANGUIS_LOAD_AOE_PROJECTILE_NAME_CASE(rocket);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
