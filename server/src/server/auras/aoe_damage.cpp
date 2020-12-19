#include <sanguis/optional_aura_type.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aoe_damage.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/collision_group.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_body_ref.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <fcppt/cast/dynamic_cross_exn.hpp>


sanguis::server::auras::aoe_damage::aoe_damage(
	sanguis::server::team const _team,
	sanguis::server::aoe const _aoe,
	sanguis::server::auras::influence const _influence,
	sanguis::server::damage::unit const _damage,
	sanguis::server::damage::modified_array const &_damage_values
)
:
	sanguis::server::auras::aura(
		sanguis::server::radius(
			_aoe.get()
		),
		sanguis::server::auras::collision_group(
			_team,
			_influence
		)
	),
	damage_(
		_damage
	),
	damage_values_(
		_damage_values
	)
{
}

sanguis::server::auras::aoe_damage::~aoe_damage()
= default;

sanguis::optional_aura_type
sanguis::server::auras::aoe_damage::type() const
{
	return
		sanguis::optional_aura_type();
}

void
sanguis::server::auras::aoe_damage::enter(
	sanguis::server::entities::with_body_ref const _with_body,
	sanguis::collision::world::created
)
{
	fcppt::cast::dynamic_cross_exn<
		sanguis::server::entities::with_health &
	>(
		_with_body.get()
	).damage(
		damage_,
		damage_values_
	);
}

void
sanguis::server::auras::aoe_damage::leave(
	sanguis::server::entities::with_body &
)
{
}
