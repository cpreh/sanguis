#include "freeze.hpp"
#include "../entities/entity.hpp"
#include "../entities/property.hpp"
#include <sge/optional_impl.hpp>

sanguis::server::auras::freeze::freeze(
	space_unit const radius,
	team::type const team
)
:
	aura(
		radius,
		team,
		influence::debuff,
		optional_groups()
	)
{}

void
sanguis::server::auras::freeze::enter(
	entities::entity &target
)
{
	target.property(
		entities::property_type::movement_speed).max(
			static_cast<space_unit>(0)
	);

	target.property(
		entities::property_type::attack_speed).max(
			static_cast<space_unit>(0)
	);
}

void
sanguis::server::auras::freeze::leave(
	entities::entity &target
)
{
	// FIXME	
}
