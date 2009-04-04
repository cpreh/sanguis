#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"

namespace sanguis 
{
namespace server
{
namespace weapons
{
class shotgun : public weapon {
public:
	shotgun(
		server::environment const &,
		weapon_type::type,
		time_type base_cooldown,
		space_unit spread_radius,
		unsigned shells,
		space_unit damage,
		unsigned magazine_size,
		time_type reload_time);
private:
	void do_attack(
		delayed_attack const &);
	
	space_unit spread_radius;
	unsigned   shells;
	space_unit damage;
};

}
}
}

#endif
