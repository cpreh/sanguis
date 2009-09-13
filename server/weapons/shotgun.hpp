#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "magazine_size.hpp"
#include "reload_time.hpp"
#include "damage.hpp"

namespace sanguis 
{
namespace server
{
namespace weapons
{

class shotgun : public weapon {
public:
	shotgun(
		weapon_type::type,
		weapons::base_cooldown,
		space_unit spread_radius,
		unsigned shells,
		weapons::damage,
		weapons::magazine_size,
		weapons::reload_time
	);
private:
	void
	do_attack(
		delayed_attack const &
	);
	
	space_unit const spread_radius;
	unsigned const shells;
	weapons::damage const damage_;
};

}
}
}

#endif
