#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>

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
	FCPPT_MAKE_STRONG_TYPEDEF(
		server::space_unit,
		spread_radius
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		unsigned,
		shells
	);

	shotgun(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		weapon_type::type,
		weapons::base_cooldown,
		spread_radius,
		shells,
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

	sanguis::random_generator &random_generator_;

	spread_radius const spread_radius_;

	shells const shells_;

	weapons::damage const damage_;
};

}
}
}

#endif
