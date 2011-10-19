#include <sanguis/load/weapon_pickup_name.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/text.hpp>

fcppt::string const
sanguis::load::weapon_pickup_name(
	weapon_type::type const _type
)
{
	switch(
		_type
	)
	{
	case weapon_type::pistol:
		return FCPPT_TEXT("pickups/pistol");
	case weapon_type::shotgun:
		return FCPPT_TEXT("pickups/shotgun");
	case weapon_type::rocket_launcher:
		return FCPPT_TEXT("pickups/rocket_launcher");
	case weapon_type::grenade:
		return FCPPT_TEXT("pickups/grenade");
	case weapon_type::sentry:
		return FCPPT_TEXT("pickups/sentry");
	case weapon_type::none:
	case weapon_type::melee:
	case weapon_type::dual_pistol:
	case weapon_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
