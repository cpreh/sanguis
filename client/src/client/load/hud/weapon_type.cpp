#include <sanguis/optional_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/hud/weapon_type.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sanguis::optional_weapon_type
sanguis::client::load::hud::weapon_type(
	fcppt::string const &_name
)
{
#define SANGUIS_LOAD_HUD_WEAPON_TYPE_CASE(\
	name,\
	category\
)\
	if(\
		_name\
		==\
		FCPPT_TEXT(#name)\
	)\
		return \
			sanguis::optional_weapon_type(\
				sanguis::weapon_type(\
					sanguis::category::name\
				)\
			)

	SANGUIS_LOAD_HUD_WEAPON_TYPE_CASE(
		shotgun,
		primary_weapon_type
	);

	SANGUIS_LOAD_HUD_WEAPON_TYPE_CASE(
		pistol,
		primary_weapon_type
	);

	SANGUIS_LOAD_HUD_WEAPON_TYPE_CASE(
		rocket_launcher,
		primary_weapon_type
	);

	SANGUIS_LOAD_HUD_WEAPON_TYPE_CASE(
		sentry,
		secondary_weapon_type
	);

	SANGUIS_LOAD_HUD_WEAPON_TYPE_CASE(
		spider,
		secondary_weapon_type
	);

	SANGUIS_LOAD_HUD_WEAPON_TYPE_CASE(
		grenade,
		secondary_weapon_type
	);

#undef SANGUIS_LOAD_HUD_WEAPON_TYPE_CASE

	return
		sanguis::optional_weapon_type();
}
