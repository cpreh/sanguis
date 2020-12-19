#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/server/add_weapon_pickup_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_weapon_pickup_callback.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/weapon_pickup_candidates.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::auras::weapon_pickup_candidates::weapon_pickup_candidates(
	sanguis::server::radius const _radius,
	sanguis::server::add_weapon_pickup_callback &&_add,
	sanguis::server::remove_weapon_pickup_callback &&_remove
)
:
	sanguis::server::auras::aura(
		_radius,
		sanguis::collision::world::ghost_group::weapon_pickup_sight
	),
	add_(
		std::move(
			_add
		)
	),
	remove_(
		std::move(
			_remove
		)
	)
{
}

sanguis::server::auras::weapon_pickup_candidates::~weapon_pickup_candidates()
= default;

sanguis::optional_aura_type
sanguis::server::auras::weapon_pickup_candidates::type() const
{
	return
		sanguis::optional_aura_type();
}

void
sanguis::server::auras::weapon_pickup_candidates::enter(
	sanguis::server::entities::with_body_ref const _body,
	sanguis::collision::world::created
)
{
	this->add_(
		fcppt::make_ref(
			fcppt::cast::static_downcast<
				sanguis::server::entities::pickups::weapon &
			>(
				_body.get()
			)
		)
	);
}

void
sanguis::server::auras::weapon_pickup_candidates::leave(
	sanguis::server::entities::with_body &_body
)
{
	this->remove_(
		fcppt::cast::static_downcast<
			sanguis::server::entities::pickups::weapon &
		>(
			_body
		)
	);
}
