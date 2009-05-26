#ifndef SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SENTRY_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
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
		time_type base_cooldown,
		time_type cast_point,
		time_type reload_time,
		create_function const &sentry_weapon);
private:
	void do_attack(
		delayed_attack const &);
	
	create_function const sentry_weapon;
};

}
}
}

#endif
