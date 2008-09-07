#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED

#include "weapon.hpp"
#include "../types.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class delayed_attack;

class pistol : public weapon {
public:
	pistol(
		environment const &,
		weapon_type::type,
		time_type base_cooldown,
		space_unit damage,
		time_type cast_point);
private:
	void do_attack(
		delayed_attack const &);

	space_unit damage;
};

}
}
}

#endif
