#ifndef SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED

#include "weapon.hpp"
#include "../types.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class delayed_attack;

class melee : public weapon {
public:
	melee(
		environment const &,
		space_unit range,
		time_type base_cooldown,
		space_unit damage);
private:
	void do_attack(
		delayed_attack const &);
	space_unit damage;
};

}
}
}

#endif
