#include "freeze.hpp"
#include "../entities/entity.hpp"
#include "../entities/property.hpp"

sanguis::server::auras::freeze::freeze(
	sge::collision::world_ptr const collision_world_,
	space_unit const radius,
	team::type const team
)
:
	aura(
		collision_world_,
		radius,
		team,
		influence::debuff
	)
{}

void sanguis::server::auras::freeze::do_effect(
	entities::entity &target)
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
