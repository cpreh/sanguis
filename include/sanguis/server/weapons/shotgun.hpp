#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED

#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{

class shotgun
:
	public weapon
{
	FCPPT_NONCOPYABLE(
		shotgun
	);
public:
	shotgun(
		sanguis::diff_clock const &,
		weapon_type::type,
		weapons::base_cooldown,
		space_unit spread_radius,
		unsigned shells,
		weapons::damage,
		weapons::magazine_size,
		weapons::reload_time
	);

	~shotgun();
private:
	void
	do_attack(
		delayed_attack const &
	);

	space_unit const spread_radius_;

	unsigned const shells_;

	weapons::damage const damage_;
};

}
}
}

#endif
