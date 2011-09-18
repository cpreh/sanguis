#ifndef SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED

#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/diff_clock_fwd.hpp>
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
		sanguis::diff_clock const &,
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
