#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/client/load/primary_weapon_name.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::model::weapon_category_name
sanguis::client::load::primary_weapon_name(sanguis::primary_weapon_type const _type)
{
#define SANGUIS_PRIMARY_WEAPON_CASE(name) \
  case sanguis::primary_weapon_type::name: \
    return sanguis::model::weapon_category_name(FCPPT_TEXT(#name))

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
    SANGUIS_PRIMARY_WEAPON_CASE(melee);
    SANGUIS_PRIMARY_WEAPON_CASE(pistol);
    SANGUIS_PRIMARY_WEAPON_CASE(dual_pistols);
    SANGUIS_PRIMARY_WEAPON_CASE(shotgun);
    SANGUIS_PRIMARY_WEAPON_CASE(rocket_launcher);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);

#undef SANGUIS_PRIMARY_WEAPON_CASE
}
