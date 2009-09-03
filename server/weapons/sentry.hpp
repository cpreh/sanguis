#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED

#include "weapon.hpp"
#include "delayed_attack_fwd.hpp"
#include "base_cooldown.hpp"
#include "cast_point.hpp"
#include "reload_time.hpp"
#include "create_function.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class sentry : public weapon {
public:
	sentry(
		server::environment const &,
		weapon_type::type,
		weapons::base_cooldown,
		weapons::cast_point,
		weapons::reload_time,
		create_function const &sentry_weapon
	);
private:
	void
	do_attack(
		delayed_attack const &
	);
	
	create_function const sentry_weapon;
};

}
}
}

#endif
