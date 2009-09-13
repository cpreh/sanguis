#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED

#include "aoe_projectile.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class aoe_damage : public aoe_projectile {
public:
	aoe_damage(
		server::environment::object_ptr const,
		pos_type const &center,
		team::type team,
		space_unit radius,
		space_unit damage_per_pulse,
		unsigned pulses,
		time_type pulse_diff,
		damage::array const &damage_values
	);
private:
	void
	do_damage(
		entity &
	);
};	

}
}
}
}

#endif
