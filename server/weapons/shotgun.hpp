#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED

#include "weapon.hpp"
#include "../../messages/types.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class shotgun : public weapon {
public:
	shotgun(
		const environment &,
		weapon_type::type,
		time_type base_cooldown,
		messages::space_unit spread_radius,
		unsigned shells,
		messages::space_unit damage);
private:
	void do_attack(
		entities::entity const &from,
		messages::pos_type const &to);
	
	messages::space_unit spread_radius;
	unsigned             shells;
	messages::space_unit damage;
};

}
}
}

#endif
