#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "magazine_size.hpp"
#include "reload_time.hpp"

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
		weapons::base_cooldown,
		space_unit spread_radius,
		unsigned shells,
		space_unit damage,
		weapons::magazine_size,
		weapons::reload_time
	);
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
