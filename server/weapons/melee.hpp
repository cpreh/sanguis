#ifndef SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "../types.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{
class melee : public weapon {
public:
	melee(
		server::environment const &,
		space_unit range,
		time_type base_cooldown,
		space_unit damage);
private:
	void do_attack(
		delayed_attack const &);
	
	void on_init_attack(
		entities::entity_with_weapon &owner);
	void on_castpoint(
		entities::entity_with_weapon &owner);

	space_unit damage;
};

}
}
}

#endif
