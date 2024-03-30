#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string sanguis::load::aoe_projectile_name(sanguis::aoe_projectile_type const _type)
{
#define SANGUIS_LOAD_AOE_PROJECTILE_NAME_CASE(name) \
  case sanguis::aoe_projectile_type::name: \
    return FCPPT_TEXT(#name)

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
    SANGUIS_LOAD_AOE_PROJECTILE_NAME_CASE(grenade);
    SANGUIS_LOAD_AOE_PROJECTILE_NAME_CASE(rocket);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
