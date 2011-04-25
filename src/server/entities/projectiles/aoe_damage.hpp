#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED

#include "aoe_projectile.hpp"
#include "../with_auras.hpp"
#include "../with_health_fwd.hpp"
#include "../../damage/unit.hpp"
#include "../../damage/array.hpp"
#include "../../radius.hpp"
#include "../../team.hpp"
#include "../../../time_delta_fwd.hpp"
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
		team::type team,
		server::radius,
		damage::unit damage_per_pulse,
		unsigned pulses,
		sanguis::time_delta const &pulse_diff,
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
