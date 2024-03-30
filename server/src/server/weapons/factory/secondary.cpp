#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/weapons/factory/grenade.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>
#include <sanguis/server/weapons/factory/secondary.hpp>
#include <sanguis/server/weapons/factory/sentry.hpp>
#include <sanguis/server/weapons/factory/spider.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::server::weapons::unique_ptr sanguis::server::weapons::factory::secondary(
    sanguis::secondary_weapon_type const _type,
    sanguis::server::weapons::factory::parameters const &_parameters)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sanguis::secondary_weapon_type::grenade:
    return sanguis::server::weapons::factory::grenade(_parameters);
  case sanguis::secondary_weapon_type::sentry:
    return sanguis::server::weapons::factory::sentry(_parameters);
  case sanguis::secondary_weapon_type::spider:
    return sanguis::server::weapons::factory::spider(_parameters);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
