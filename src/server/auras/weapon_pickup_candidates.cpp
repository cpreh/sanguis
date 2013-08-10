#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/weapon_pickup_add_candidate_callback.hpp>
#include <sanguis/server/auras/weapon_pickup_candidates.hpp>
#include <sanguis/server/auras/weapon_pickup_remove_candidate_callback.hpp>
#include <sanguis/server/collision/group.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>


sanguis::server::auras::weapon_pickup_candidates::weapon_pickup_candidates(
	sanguis::server::radius const _radius,
	sanguis::server::auras::weapon_pickup_add_candidate_callback const &_add,
	sanguis::server::auras::weapon_pickup_remove_candidate_callback const &_remove
)
:
	sanguis::server::auras::aura(
		_radius,
		sanguis::server::team::neutral,
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

sanguis::server::auras::weapon_pickup_candidates::~weapon_pickup_candidates()
{
}

sanguis::server::collision::group_vector const
sanguis::server::auras::weapon_pickup_candidates::collision_groups() const
{
	return
		sanguis::server::collision::group_vector{
			sanguis::server::collision::group::weapon_pickup_sight
		};
}

void
sanguis::server::auras::weapon_pickup_candidates::enter(
	sanguis::server::entities::with_body &_body
)
{
	add_.get()(
		dynamic_cast<
			sanguis::server::entities::pickups::weapon &
		>(
			_body
		)
	);
}

void
sanguis::server::auras::weapon_pickup_candidates::leave(
	sanguis::server::entities::with_body &_body
)
{
	remove_.get()(
		dynamic_cast<
			sanguis::server::entities::pickups::weapon &
		>(
			_body
		)
	);
}
