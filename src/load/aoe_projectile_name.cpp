#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sanguis::load::aoe_projectile_name(
	sanguis::aoe_projectile_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::aoe_projectile_type::grenade:
		return FCPPT_TEXT("grenade");
	case sanguis::aoe_projectile_type::rocket:
		return FCPPT_TEXT("rocket");
	case sanguis::aoe_projectile_type::aoe_damage:
	case sanguis::aoe_projectile_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
