#include "enemy_name.hpp"
#include "../exception.hpp"
#include <fcppt/text.hpp>

fcppt::string const
sanguis::load::enemy_name(
	enemy_type::type const etype
)
{
	switch(etype)
	{
	case enemy_type::wolf_black:
		return FCPPT_TEXT("wolf_black");
	case enemy_type::wolf_brown:
		return FCPPT_TEXT("wolf_brown");
	case enemy_type::wolf_white:
		return FCPPT_TEXT("wolf_white");
	case enemy_type::zombie00:
		return FCPPT_TEXT("zombie00");
	case enemy_type::zombie01:
		return FCPPT_TEXT("zombie01");
	case enemy_type::spider:
		return FCPPT_TEXT("spider");
	case enemy_type::skeleton:
		return FCPPT_TEXT("skeleton");
	case enemy_type::maggot:
		return FCPPT_TEXT("maggot");
	}

	throw exception(
		FCPPT_TEXT("load::enemy_name: missing loading code!")
	);
}
