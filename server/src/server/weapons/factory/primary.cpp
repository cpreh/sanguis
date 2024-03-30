#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/weapons/factory/dual_pistols.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>
#include <sanguis/server/weapons/factory/pistol.hpp>
#include <sanguis/server/weapons/factory/primary.hpp>
#include <sanguis/server/weapons/factory/rocket_launcher.hpp>
#include <sanguis/server/weapons/factory/shotgun.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::server::weapons::unique_ptr sanguis::server::weapons::factory::primary(
    sanguis::primary_weapon_type const _type,
    sanguis::server::weapons::factory::parameters const &_parameters)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sanguis::primary_weapon_type::melee:
    break;
  case sanguis::primary_weapon_type::pistol:
    return sanguis::server::weapons::factory::pistol(_parameters);
  case sanguis::primary_weapon_type::dual_pistols:
    return sanguis::server::weapons::factory::dual_pistols(_parameters);
  case sanguis::primary_weapon_type::shotgun:
    return sanguis::server::weapons::factory::shotgun(_parameters);
  case sanguis::primary_weapon_type::rocket_launcher:
    return sanguis::server::weapons::factory::rocket_launcher(_parameters);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
