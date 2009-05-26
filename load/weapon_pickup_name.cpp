#include "weapon_pickup_name.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>

sge::string const
sanguis::load::weapon_pickup_name(
	weapon_type::type const wtype)
{
	switch(wtype) {
	case weapon_type::pistol:
		return SGE_TEXT("pickups/pistol");
	case weapon_type::shotgun:
		return SGE_TEXT("pickups/shotgun");
	case weapon_type::rocket_launcher:
		return SGE_TEXT("pickups/rocket_launcher");
	case weapon_type::grenade:
		return SGE_TEXT("pickups/grenade");
	case weapon_type::sentry:
		return SGE_TEXT("pickups/pistol");//sentry"); // FIXME: nille, add the sentry pickup!
	default:
		throw exception(
			SGE_TEXT("load::weapon_pickup_name: missing loading code!"));
	}
}
