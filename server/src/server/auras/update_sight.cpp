#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/server/add_sight_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_sight_callback.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/update_sight.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/cast/try_dynamic.hpp>


sanguis::server::auras::update_sight::update_sight(
	sanguis::server::radius const _radius,
	sanguis::server::add_sight_callback const &_add,
	sanguis::server::remove_sight_callback const &_remove
)
:
	sanguis::server::auras::aura(
		_radius,
		sanguis::collision::world::group::sight_range
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

void
sanguis::server::auras::update_sight::enter(
	sanguis::server::entities::with_body &_entity
)
{
	fcppt::maybe_void(
		fcppt::cast::try_dynamic<
			sanguis::server::entities::with_id const &
		>(
			_entity
		),
		[
			this
		](
			sanguis::server::entities::with_id const &_with_id
		)
		{
			add_.get()(
				_with_id.id()
			);
		}
	);
}

void
sanguis::server::auras::update_sight::leave(
	sanguis::server::entities::with_body &_entity
)
{
	fcppt::maybe_void(
		fcppt::cast::try_dynamic<
			sanguis::server::entities::with_id const &
		>(
			_entity
		),
		[
			this
		](
			sanguis::server::entities::with_id const &_with_id
		)
		{
			remove_.get()(
				_with_id.id()
			);
		}
	);
}
