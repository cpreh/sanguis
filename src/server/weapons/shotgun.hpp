#ifndef SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SHOTGUN_HPP_INCLUDED

#include "delayed_attack_fwd.hpp"
#include "weapon.hpp"
#include "base_cooldown.hpp"
#include "magazine_size.hpp"
#include "reload_time.hpp"
#include "damage.hpp"
#include "../../diff_clock_fwd.hpp"
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
