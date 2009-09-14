#include "update_sight.hpp"
#include "../entities/entity.hpp"

sanguis::server::auras::update_sight::update_sight(
	sge::collision::world_ptr const collision_world_,
	space_unit const radius_,
	update_sight_function const &update_sight_function_
)
:
	aura(
		collision_world_,
		radius_,
		team::neutral,
		influence::debuff
	),
	update_sight_function_(
		update_sight_function_
	)
{}

void
sanguis::server::auras::update_sight::do_effect(
	entities::entity &e
)
{
	update_sight_function_(
		e.id()
	);
}