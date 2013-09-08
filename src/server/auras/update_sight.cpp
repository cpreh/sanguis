#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/server/enter_sight_function.hpp>
#include <sanguis/server/leave_sight_function.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/update_sight.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <fcppt/try_dynamic_cast.hpp>


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

sanguis::collision::world::group_field const
sanguis::server::auras::update_sight::collision_groups() const
{
	return
		sanguis::collision::world::group_field{
			sanguis::collision::world::group::sight_range
		};
}

void
sanguis::server::auras::update_sight::enter(
	sanguis::server::entities::with_body &_entity
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_id const *,
		with_id,
		&_entity
	)
		(
			enter_.get()
		)
		(
			with_id->id()
		);
}

void
sanguis::server::auras::update_sight::leave(
	sanguis::server::entities::with_body &_entity
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_id const *,
		with_id,
		&_entity
	)

		(
			leave_.get()
		)
		(
			with_id->id()
		);
}
