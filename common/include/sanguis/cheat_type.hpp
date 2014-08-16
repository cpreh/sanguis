#ifndef SANGUIS_CHEAT_TYPE_HPP_INCLUDED
#define SANGUIS_CHEAT_TYPE_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>


namespace sanguis
{

enum class cheat_type
{
	exp,
	heal,
	kill,
	friendly_spider,
	monster_spawner,
	perks,
	rocket_launcher,
	sentry,
	shotgun,
	grenade,
	fcppt_maximum = grenade
};

}

#endif
