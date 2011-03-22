#include "update_sight.hpp"
#include "../entities/base.hpp"
#include <fcppt/assign/make_container.hpp>
#include <fcppt/optional_impl.hpp>

sanguis::server::auras::update_sight::update_sight(
	space_unit const _radius,
	update_sight_function const &_enter,
	update_sight_function const &_nleave // VC++ doesn't like _leave
)
:
	aura(
		_radius,
		team::neutral,
		influence::debuff
	),
	enter_(
		_enter
	),
	leave_(
		_nleave
	)
{
}

sanguis::server::auras::update_sight::~update_sight()
{
}

sanguis::server::collision::group_vector const
sanguis::server::auras::update_sight::collision_groups() const
{
	return
		fcppt::assign::make_container<
			collision::group_vector
		>(
			collision::group::sight_range
		);
}

void
sanguis::server::auras::update_sight::enter(
	entities::base &_entity
)
{
	enter_(
		_entity.id()
	);
}

void
sanguis::server::auras::update_sight::leave(
	entities::base &_entity
)
{
	leave_(
		_entity.id()
	);
}
