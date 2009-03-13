#include "aoe_damage.hpp"
#include "../property.hpp"
#include "../../buffs/burn.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	server::environment const &env,
	pos_type const &center,
	team::type const team_,
	space_unit const radius,
	space_unit const damage_per_pulse,
	unsigned const max_pulses,
	time_type const pulse_diff,
	damage_array const &damage_values)
:
	projectile(
		projectile_type::aoe_damage,
		env,
		center,
		messages::mu(0),
		team_,
		boost::assign::map_list_of
			(	
				entities::property_type::health,
				entities::property(messages::mu(1))
			),
		dim_type(
			radius * messages::mu(2),
			radius * messages::mu(2)),
		pulse_diff * static_cast<time_type>(max_pulses)),
	pulse_diff(pulse_diff),
	damage_per_pulse(damage_per_pulse),
	damage_values(damage_values)
{}

void sanguis::server::entities::projectiles::aoe_damage::collision(
	entity &e)
{
	e.add_buff(
		buffs::auto_ptr(
			new buffs::burn(
				id(),
				damage_per_pulse,
				pulse_diff,
				1,
				damage_values
			)
		)
	);
}
