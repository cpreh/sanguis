#ifndef SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_PISTOL_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "cast_point.hpp"
#include "magazine_size.hpp"
#include "reload_time.hpp"
#include "range.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

class pistol : public weapon {
public:
	pistol(
		server::environment const &,
		weapon_type::type,
		weapons::base_cooldown,
		space_unit damage,
		weapons::cast_point,
		weapons::magazine_size,
		weapons::reload_time,
		weapons::range
	);
private:
	void do_attack(
		delayed_attack const &);

	space_unit const damage;
};

}
}
}

#endif
