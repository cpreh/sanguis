#include "aoe_damage.hpp"
#include <sge/time/second.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	environment const &env,
	pos_type const &center,
	team::type const team_,
	space_unit const radius,
	space_unit const damage_per_pulse,
	unsigned const max_pulses,
	time_type const pulse_diff,
	damage_array const &damage_values)
:
	projectile(
		env,
		center,
		messages::mu(0),
		team_,
		property_map(),
		dim_type(
			radius * messages::mu(2),
			radius * messages::mu(2)),
		static_cast<time_type>(
			max_pulses) * pulse_diff),
	diff_clock_(),
	damage_per_pulse(damage_per_pulse),
	pulses(0),
	max_pulses(max_pulses),
	pulse_timer(
		sge::time::second(
			pulse_diff),
		true,
		diff_clock_.callback()),
	damage_values(damage_values)
{}

void sanguis::server::entities::projectiles::aoe_damage::do_hit(
	hit_vector const &hits)
{
	if(!pulse_timer.update_b())
		return;
	
	if(pulses == max_pulses)
		die();
	
	BOOST_FOREACH(hit_vector::value_type e, hits)
		e.get().damage(
			damage_per_pulse,
			damage_values);
	
	++pulses;
}
