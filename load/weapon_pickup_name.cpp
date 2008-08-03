#include "weapon_pickup_name.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::string const sanguis::load::weapon_pickup_name(
	weapon_type::type const wtype)
{
	switch(wtype) {
	case weapon_type::pistol:
		return SGE_TEXT("pickup_pistol");
	case weapon_type::shotgun:
		return SGE_TEXT("pickup_shotgun");
	default:
		throw sge::exception(
			SGE_TEXT("load::weapon_pickup_name: missing loading code!"));
	}
}
