#include "aoe_damage.hpp"
#include "../property.hpp"
#include "../../auras/burn.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/container/map_impl.hpp>

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
		static_cast<space_unit>(0),
		team_,
		property_map(),
		dim_type(
			radius * static_cast<space_unit>(2),
			radius * static_cast<space_unit>(2)),
		pulse_diff * static_cast<time_type>(max_pulses))
{
	add_aura(
		auras::auto_ptr(
			new auras::burn(
				environment(),
				radius,
				team_,
				damage_per_pulse,
				pulse_diff,
				damage_values
			)
		)
	);
}

void
sanguis::server::entities::projectiles::aoe_damage::do_damage(
	entity &)
{}
