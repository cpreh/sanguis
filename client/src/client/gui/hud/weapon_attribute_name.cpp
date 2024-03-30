#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_name.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::font::string
sanguis::client::gui::hud::weapon_attribute_name(sanguis::weapon_attribute_type const _type)
{
#define SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(name) \
  case sanguis::weapon_attribute_type::name: \
    return SGE_FONT_LIT(#name)

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
    SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(accuracy);

    SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(aoe);

    SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(damage);

    SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(health);

    SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(shells);

    SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(spread_radius);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
