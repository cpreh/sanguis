#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/load/weapon_pickup_name_visitor.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::load::weapon_pickup_name_visitor::result_type
sanguis::load::weapon_pickup_name_visitor::operator()(
	sanguis::primary_weapon_type const _type
) const
{
	switch(
		_type
	)
	{
	case sanguis::primary_weapon_type::pistol:
		return FCPPT_TEXT("pickups/pistol");
	case sanguis::primary_weapon_type::shotgun:
		return FCPPT_TEXT("pickups/shotgun");
	case sanguis::primary_weapon_type::rocket_launcher:
		return FCPPT_TEXT("pickups/rocket_launcher");
	case sanguis::primary_weapon_type::dual_pistols:
	case sanguis::primary_weapon_type::melee:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sanguis::load::weapon_pickup_name_visitor::result_type
sanguis::load::weapon_pickup_name_visitor::operator()(
	sanguis::secondary_weapon_type const _type
) const
{
	switch(
		_type
	)
	{
	case sanguis::secondary_weapon_type::grenade:
		return FCPPT_TEXT("pickups/grenade");
	case sanguis::secondary_weapon_type::sentry:
		return FCPPT_TEXT("pickups/sentry");
	}

	FCPPT_ASSERT_UNREACHABLE;
}
