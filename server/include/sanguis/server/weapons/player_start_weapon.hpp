#ifndef SANGUIS_SERVER_WEAPONS_PLAYER_START_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PLAYER_START_WEAPON_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

sanguis::server::weapons::unique_ptr
player_start_weapon(
	sanguis::diff_clock const &,
	sanguis::random_generator &
);

}
}
}

#endif
