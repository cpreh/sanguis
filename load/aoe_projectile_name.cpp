#include "aoe_projectile_name.hpp"
#include "../exception.hpp"
#include <fcppt/text.hpp>

fcppt::string const
sanguis::load::aoe_projectile_name(
	aoe_projectile_type::type const ptype
)
{
	switch(ptype)
	{
	case aoe_projectile_type::grenade:
		return FCPPT_TEXT("grenade");
	case aoe_projectile_type::rocket:
		return FCPPT_TEXT("rocket");
	}

	throw exception(
		FCPPT_TEXT("load::aoe_projectile_name: missing loading code!")
	);
}
