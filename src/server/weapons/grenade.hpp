#ifndef SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "damage.hpp"
#include "aoe.hpp"
#include "cast_point.hpp"
#include "reload_time.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class grenade
:
	public weapon
{
	FCPPT_NONCOPYABLE(
		grenade
	);
public:
	grenade(
		weapon_type::type,
		weapons::base_cooldown,
		weapons::damage,
		weapons::aoe,
		weapons::cast_point,
		weapons::reload_time
	);
	
	~grenade();
private:
	void
	do_attack(
		delayed_attack const &
	);
	
	weapons::damage const damage_;

	weapons::aoe const aoe_;
};

}
}
}

#endif
