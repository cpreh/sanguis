#ifndef SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class grenade : public weapon {
public:
	grenade(
		server::environment const &,
		weapon_type::type,
		time_type base_cooldown,
		space_unit damage,
		space_unit radius,
		time_type cast_point,
		time_type reload_time);
private:
	void do_attack(
		delayed_attack const &);
	
	space_unit const
		damage,
		radius;
};

}
}
}

#endif
