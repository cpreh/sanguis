#ifndef SANGUIS_WEAPON_TYPE_HPP_INCLUDED
#define SANGUIS_WEAPON_TYPE_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>


namespace sanguis
{

enum class weapon_type
{
	melee,
	pistol,
	dual_pistol,
	shotgun,
	rocket_launcher,
	grenade,
	sentry,
	fcppt_maximum = sentry
};

}

#endif
