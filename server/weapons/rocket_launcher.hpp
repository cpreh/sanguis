#ifndef SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "damage.hpp"
#include "magazine_size.hpp"
#include "reload_time.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class rocket_launcher : public weapon {
public:
	rocket_launcher(
		server::environment const &,
		weapon_type::type,
		weapons::base_cooldown,
		weapons::damage,
		space_unit rocket_aoe,
		weapons::magazine_size,
		weapons::reload_time
	);
private:
	void
	do_attack(
		delayed_attack const &
	);
	
	weapons::damage const damage_;
	space_unit const rocket_aoe;
};

}
}
}

#endif
