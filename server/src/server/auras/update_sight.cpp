#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/server/add_sight_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_sight_callback.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/update_sight.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <fcppt/try_dynamic_cast.hpp>


sanguis::server::auras::update_sight::update_sight(
	sanguis::server::radius const _radius,
	sanguis::server::add_sight_callback const &_add,
	sanguis::server::remove_sight_callback const &_remove
)
:
	sanguis::server::auras::aura(
		_radius,
		// TODO: This doesn't make any sense here
		sanguis::server::team::players,
		sanguis::server::auras::influence::debuff
	),
	add_(
		_add
	),
	remove_(
		_remove
	)
{
}

sanguis::server::auras::update_sight::~update_sight()
{
}

sanguis::optional_aura_type const
sanguis::server::auras::update_sight::type() const
{
	return
		sanguis::optional_aura_type();
}

sanguis::collision::world::group
sanguis::server::auras::update_sight::collision_group() const
{
	return
		sanguis::collision::world::group::sight_range;
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
			add_.get()
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
			remove_.get()
		)
		(
			with_id->id()
		);
}
