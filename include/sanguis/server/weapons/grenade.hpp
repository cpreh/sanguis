#ifndef SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_GRENADE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class grenade
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		grenade
	);
public:
	grenade(
		sanguis::diff_clock const &,
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::damage,
		sanguis::server::weapons::aoe,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::reload_time,
		sanguis::server::weapons::range
	);

	~grenade();
private:
	void
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	);

	sanguis::server::weapons::damage const damage_;

	sanguis::server::weapons::aoe const aoe_;
};

}
}
}

#endif
