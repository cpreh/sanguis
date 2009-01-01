#ifndef SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED

#include "weapon.hpp"
#include "../types.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class delayed_attack;

class rocket_launcher : public weapon {
public:
	rocket_launcher(
		server::environment const &,
		weapon_type::type,
		time_type base_cooldown,
		space_unit rocket_damage,
		space_unit rocket_aoe,
		unsigned magazine_size,
		time_type cooldown);
private:
	void do_attack(
		delayed_attack const &);
	
	space_unit rocket_damage,
	           rocket_aoe;
};

}
}
}

#endif
