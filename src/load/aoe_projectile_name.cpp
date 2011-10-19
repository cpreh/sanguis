#include <sanguis/load/aoe_projectile_name.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/text.hpp>

fcppt::string const
sanguis::load::aoe_projectile_name(
	aoe_projectile_type::type const _type
)
{
	switch(
		_type
	)
	{
	case aoe_projectile_type::grenade:
		return FCPPT_TEXT("grenade");
	case aoe_projectile_type::rocket:
		return FCPPT_TEXT("rocket");
	case aoe_projectile_type::aoe_damage:
	case aoe_projectile_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
