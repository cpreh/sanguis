#include <sanguis/cheat_type.hpp>
#include <sanguis/optional_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/cheat/weapon_type.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::optional_weapon_type
sanguis::server::cheat::weapon_type(sanguis::cheat_type const _cheat_type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_cheat_type)
  {
  case sanguis::cheat_type::auras:
  case sanguis::cheat_type::exp:
  case sanguis::cheat_type::heal:
  case sanguis::cheat_type::kill:
  case sanguis::cheat_type::monster_spawner:
  case sanguis::cheat_type::perks:
    return sanguis::optional_weapon_type{};
  case sanguis::cheat_type::sentry:
    return sanguis::optional_weapon_type{
        sanguis::weapon_type(sanguis::secondary_weapon_type::sentry)};
  case sanguis::cheat_type::spider:
    return sanguis::optional_weapon_type{
        sanguis::weapon_type(sanguis::secondary_weapon_type::spider)};
  case sanguis::cheat_type::grenade:
    return sanguis::optional_weapon_type{
        sanguis::weapon_type(sanguis::secondary_weapon_type::grenade)};
  case sanguis::cheat_type::shotgun:
    return sanguis::optional_weapon_type{
        sanguis::weapon_type(sanguis::primary_weapon_type::shotgun)};
  case sanguis::cheat_type::rocket_launcher:
    return sanguis::optional_weapon_type{
        sanguis::weapon_type(sanguis::primary_weapon_type::rocket_launcher)};
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_cheat_type);
}
