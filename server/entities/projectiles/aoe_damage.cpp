#include "aoe_damage.hpp"
#include "../../auras/burn.hpp"
#include "../../environment/object.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <sge/optional_impl.hpp>

sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	team::type const team_,
	space_unit const radius,
	damage::unit const damage_per_pulse,
	unsigned const max_pulses,
	time_type const pulse_diff,
	damage::array const &damage_values
)
:
	aoe_projectile(
		aoe_projectile_type::aoe_damage,
		team_,
		entities::movement_speed(0),
		dim_type(
			radius * static_cast<space_unit>(2),
			radius * static_cast<space_unit>(2)
		),
		life_time(
			pulse_diff
			* static_cast<
				time_type
			>(
				max_pulses
			)
		),
		indeterminate::yes,
		radius,
		static_cast<space_unit>(0)
	)
{
	add_aura(
		auras::auto_ptr(
			new auras::burn(
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
sanguis::server::entities::projectiles::aoe_damage::on_update(
	time_type const time_
)
{
	projectile::on_update(
		time_
	);

	with_auras::on_update(
		time_
	);
}

void
sanguis::server::entities::projectiles::aoe_damage::do_damage(
	with_health &
)
{}
