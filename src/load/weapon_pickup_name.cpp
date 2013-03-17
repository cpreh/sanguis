#include <sanguis/weapon_type.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sanguis::load::weapon_pickup_name(
	sanguis::weapon_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::weapon_type::pistol:
		return FCPPT_TEXT("pickups/pistol");
	case sanguis::weapon_type::shotgun:
		return FCPPT_TEXT("pickups/shotgun");
	case sanguis::weapon_type::rocket_launcher:
		return FCPPT_TEXT("pickups/rocket_launcher");
	case sanguis::weapon_type::grenade:
		return FCPPT_TEXT("pickups/grenade");
	case sanguis::weapon_type::sentry:
		return FCPPT_TEXT("pickups/sentry");
	case sanguis::weapon_type::none:
	case sanguis::weapon_type::melee:
	case sanguis::weapon_type::dual_pistol:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
