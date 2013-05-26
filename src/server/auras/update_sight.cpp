#include <sanguis/server/enter_sight_function.hpp>
#include <sanguis/server/leave_sight_function.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/update_sight.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::server::auras::update_sight::update_sight(
	sanguis::server::radius const _radius,
	sanguis::server::enter_sight_function const &_enter,
	sanguis::server::leave_sight_function const &_leave
)
:
	sanguis::server::auras::aura(
		_radius,
		sanguis::server::team::neutral,
		sanguis::server::auras::influence::debuff
	),
	enter_(
		_enter
	),
	leave_(
		_leave
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
			sanguis::server::collision::group_vector
		>(
			sanguis::server::collision::group::sight_range
		);
}

void
sanguis::server::auras::update_sight::enter(
	sanguis::server::entities::with_body &_entity
)
{
	(
		enter_.get()
	)
	(
		_entity.id()
	);
}

void
sanguis::server::auras::update_sight::leave(
	sanguis::server::entities::with_body &_entity
)
{
	(
		leave_.get()
	)
	(
		_entity.id()
	);
}
