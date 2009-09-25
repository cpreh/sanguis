#ifndef SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "range.hpp"
#include "base_cooldown.hpp"
#include "damage.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class melee
:
	public weapon
{
public:
	melee(
		weapons::range,
		weapons::base_cooldown,
		weapons::damage
	);
private:
	void
	do_attack(
		delayed_attack const &
	);
	
	void
	on_init_attack(
		entities::with_weapon &owner
	);
	
	void
	on_castpoint(
		entities::with_weapon &owner
	);

	weapons::damage const damage_;
};

}
}
}

#endif
