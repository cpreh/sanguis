#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
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
	public sanguis::server::entities::projectiles::projectile
{
	FCPPT_NONCOPYABLE(
		melee
	);
public:
	melee(
		sanguis::diff_clock const &,
		sanguis::server::team,
		sanguis::server::damage::unit
	);

	~melee();
private:
	void
	do_damage(
		sanguis::server::entities::with_health &
	);

	sanguis::server::damage::unit const damage_;
};

}
}
}
}

#endif
