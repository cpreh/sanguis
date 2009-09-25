#include "update_sight.hpp"
#include "../entities/base.hpp"
#include <sge/assign/make_container.hpp>
#include <sge/optional_impl.hpp>

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

sanguis::server::collision::group_vector const
sanguis::server::auras::update_sight::collision_groups() const
{
	return
		sge::assign::make_container<
			collision::group_vector
		>(
			collision::group::sight_range
		);
}

void
sanguis::server::auras::update_sight::enter(
	entities::base &e
)
{
	enter_(
		e.id()
	);
}

void
sanguis::server::auras::update_sight::leave(
	entities::base &e
)
{
	leave_(
		e.id()
	);
}
