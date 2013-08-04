#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/weapon_type.hpp>
#include <fcppt/assert/unreachable.hpp>


bool
sanguis::is_primary_weapon(
	sanguis::weapon_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::weapon_type::melee:
	case sanguis::weapon_type::pistol:
	case sanguis::weapon_type::dual_pistol:
	case sanguis::weapon_type::shotgun:
	case sanguis::weapon_type::rocket_launcher:
		return true;
	case sanguis::weapon_type::grenade:
	case sanguis::weapon_type::sentry:
		return false;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
