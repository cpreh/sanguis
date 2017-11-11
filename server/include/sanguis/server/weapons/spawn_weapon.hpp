#ifndef SANGUIS_SERVER_WEAPONS_SPAWN_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SPAWN_WEAPON_HPP_INCLUDED

#include <sanguis/server/weapons/create_function.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::weapons::create_function,
	spawn_weapon
);

}
}
}

#endif
