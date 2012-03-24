#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED

#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class aoe_damage
:
	public aoe_projectile,
	public with_auras
{
	FCPPT_NONCOPYABLE(
		aoe_damage
	);
public:
	aoe_damage(
		sanguis::diff_clock const &,
		team::type team,
		server::radius,
		damage::unit damage_per_pulse,
		unsigned pulses,
		sanguis::duration const &pulse_diff,
		damage::array const &damage_values
	);

	~aoe_damage();
private:
	void
	do_damage(
		with_health &
	);
};

}
}
}
}

#endif
