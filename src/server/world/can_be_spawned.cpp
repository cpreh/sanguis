#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/world/can_be_spawned.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <fcppt/try_dynamic_cast.hpp>


bool
sanguis::server::world::can_be_spawned(
	sge::projectile::world const &_world,
	sge::projectile::body::object const &_static_body,
	sanguis::server::entities::base const &_entity
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_body const *,
		with_body,
		&_entity
	)
	{
	/*
		return
			_world.collides(
				with_body->body().get(),
				_static_body
			);*/
	}

	// Entities without bodies fit everywhere
	return true;
}
