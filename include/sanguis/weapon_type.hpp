#ifndef SANGUIS_WEAPON_TYPE_HPP_INCLUDED
#define SANGUIS_WEAPON_TYPE_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>


namespace sanguis
{

enum class weapon_type
{
	none,
	melee,
	pistol,
	dual_pistol,
	shotgun,
	rocket_launcher,
	grenade,
	sentry,
	size
};

}

#endif
