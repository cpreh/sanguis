#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED

#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class melee
:
	public projectile
{
	FCPPT_NONCOPYABLE(
		melee
	);
public:
	melee(
		sanguis::diff_clock const &,
		team::type team,
		damage::unit
	);

	~melee();
private:
	void
	do_damage(
		with_health &
	);

	damage::unit const damage_;
};

}
}
}
}

#endif
