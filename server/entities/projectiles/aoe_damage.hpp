#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED

#include "projectile.hpp"
#include "../../../diff_clock.hpp"
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class aoe_damage : public projectile {
public:
	aoe_damage(
		environment const &,
		pos_type const &center,
		team::type team,
		space_unit radius,
		space_unit damage_per_pulse,
		unsigned pulses,
		time_type pulse_diff,
		damage_array const &damage_values);
private:
	void update(
		time_type,
		container &);
	
	void do_hit(
		hit_vector const &);	
	
	diff_clock       diff_clock_;
	space_unit       damage_per_pulse;
	unsigned         pulses;
	unsigned const   max_pulses;
	sge::time::timer pulse_timer;
	damage_array     damage_values;
};

}
}
}
}

#endif
