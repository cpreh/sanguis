#ifndef SANGUIS_SERVER_WEAPONS_PLAYER_START_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PLAYER_START_WEAPON_HPP_INCLUDED

#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

sanguis::server::weapons::unique_ptr
player_start_weapon(
	sanguis::server::weapons::common_parameters const &
);

}
}
}

#endif
