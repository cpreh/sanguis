#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/client/gui/hud/weapon_name.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/variant/match.hpp>

sge::font::string sanguis::client::gui::hud::weapon_name(sanguis::weapon_type const &_weapon_type)
{
  return fcppt::variant::match(
      _weapon_type,
      [](sanguis::primary_weapon_type const _primary_type)
      {
#define SANGUIS_WEAPON_NAME_PRIMARY_CASE(name, value) \
  case sanguis::primary_weapon_type::name: \
    return value
        switch (_primary_type)
        {
          SANGUIS_WEAPON_NAME_PRIMARY_CASE(melee, SGE_FONT_LIT("Melee"));

          SANGUIS_WEAPON_NAME_PRIMARY_CASE(pistol, SGE_FONT_LIT("Pistol"));

          SANGUIS_WEAPON_NAME_PRIMARY_CASE(dual_pistols, SGE_FONT_LIT("Dual Pistol"));

          SANGUIS_WEAPON_NAME_PRIMARY_CASE(shotgun, SGE_FONT_LIT("Shotgun"));

          SANGUIS_WEAPON_NAME_PRIMARY_CASE(rocket_launcher, SGE_FONT_LIT("Rocket Launcher"));
        }

#undef SANGUIS_WEAPON_NAME_PRIMARY_CASE

        FCPPT_ASSERT_UNREACHABLE;
      },
      [](sanguis::secondary_weapon_type const _secondary_type)
      {
#define SANGUIS_WEAPON_NAME_SECONDARY_CASE(name, value) \
  case sanguis::secondary_weapon_type::name: \
    return value
        switch (_secondary_type)
        {
          SANGUIS_WEAPON_NAME_SECONDARY_CASE(grenade, SGE_FONT_LIT("Grenade"));

          SANGUIS_WEAPON_NAME_SECONDARY_CASE(sentry, SGE_FONT_LIT("Sentry"));

          SANGUIS_WEAPON_NAME_SECONDARY_CASE(spider, SGE_FONT_LIT("Spider"));
        }

#undef SANGUIS_WEAPON_NAME_SECONDARY_CASE

        FCPPT_ASSERT_UNREACHABLE;
      });
}
