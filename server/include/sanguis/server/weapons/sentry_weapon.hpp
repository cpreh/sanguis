#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_WEAPON_HPP_INCLUDED

#include <sanguis/server/weapons/create_function.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::weapons::create_function,
	sentry_weapon
);

}
}
}

#endif
