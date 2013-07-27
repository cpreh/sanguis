#ifndef SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MELEE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class melee
:
	public sanguis::server::weapons::weapon
{
	FCPPT_NONCOPYABLE(
		melee
	);
public:
	melee(
		sanguis::diff_clock const &,
		sanguis::server::weapons::range,
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::damage
	);

	~melee();
private:
	void
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	);

	sanguis::server::weapons::damage const damage_;
};

}
}
}

#endif
