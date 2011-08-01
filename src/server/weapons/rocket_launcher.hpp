#ifndef SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ROCKET_LAUNCHER_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "damage.hpp"
#include "aoe.hpp"
#include "magazine_size.hpp"
#include "reload_time.hpp"
#include "../../diff_clock_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class rocket_launcher
:
	public weapon
{
	FCPPT_NONCOPYABLE(
		rocket_launcher
	);
public:
	rocket_launcher(
		sanguis::diff_clock const &,
		weapon_type::type,
		weapons::base_cooldown,
		weapons::damage,
		weapons::aoe,
		weapons::magazine_size,
		weapons::reload_time
	);

	~rocket_launcher();
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
