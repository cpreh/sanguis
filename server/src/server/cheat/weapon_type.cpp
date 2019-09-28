#include <sanguis/cheat_type.hpp>
#include <sanguis/optional_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/cheat/weapon_type.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::optional_weapon_type
sanguis::server::cheat::weapon_type(
	sanguis::cheat_type const _cheat_type
)
{
	switch(
		_cheat_type
	)
	{
	case sanguis::cheat_type::exp:
	case sanguis::cheat_type::heal:
	case sanguis::cheat_type::kill:
	case sanguis::cheat_type::monster_spawner:
	case sanguis::cheat_type::perks:
		return
			sanguis::optional_weapon_type{};
	case sanguis::cheat_type::sentry:
		return
			sanguis::optional_weapon_type{
				sanguis::weapon_type(
					sanguis::secondary_weapon_type::sentry
				)
			};
	case sanguis::cheat_type::spider:
		return
			sanguis::optional_weapon_type{
				sanguis::weapon_type(
					sanguis::secondary_weapon_type::spider
				)
			};
	case sanguis::cheat_type::grenade:
		return
			sanguis::optional_weapon_type{
				sanguis::weapon_type(
					sanguis::secondary_weapon_type::grenade
				)
			};
	case sanguis::cheat_type::shotgun:
		return
			sanguis::optional_weapon_type{
				sanguis::weapon_type(
					sanguis::primary_weapon_type::shotgun
				)
			};
	case sanguis::cheat_type::rocket_launcher:
		return
			sanguis::optional_weapon_type{
				sanguis::weapon_type(
					sanguis::primary_weapon_type::rocket_launcher
				)
			};
	}

	FCPPT_ASSERT_UNREACHABLE;
}
