#include "update_sight.hpp"
#include "../entities/entity.hpp"

sanguis::server::auras::update_sight::update_sight(
	space_unit const radius_,
	update_sight_function const &enter_,
	update_sight_function const &leave_
)
:
	aura(
		radius_,
		team::neutral,
		influence::debuff
	),
	enter_(
		enter_	
	),
	leave_(
		leave_
	)
{}

void
sanguis::server::auras::update_sight::enter(
	entities::entity &e
)
{
	enter_(
		e.id()
	);
}

void
sanguis::server::auras::update_sight::leave(
	entities::entity &e
)
{
	leave_(
		e.id()
	);
}
