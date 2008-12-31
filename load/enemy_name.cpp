#include "enemy_name.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>

sge::string const
sanguis::load::enemy_name(
	enemy_type::type const etype)
{
	switch(etype) {
	case enemy_type::wolf_black:
		return SGE_TEXT("wolf_black");
	case enemy_type::wolf_brown:
		return SGE_TEXT("wolf_brown");
	case enemy_type::wolf_white:
		return SGE_TEXT("wolf_white");
	case enemy_type::zombie00:
		return SGE_TEXT("zombie00");
	case enemy_type::zombie01:
		return SGE_TEXT("zombie01");
	case enemy_type::spider:
		return SGE_TEXT("spider");
	case enemy_type::skeleton:
		return SGE_TEXT("skeleton");
	case enemy_type::maggot:
		return SGE_TEXT("maggot");
	default:
		throw exception(
			SGE_TEXT("load::enemy_name: missing loading code!"));
	}
}
