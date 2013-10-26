#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aoe_damage.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	sanguis::server::team const _team,
	sanguis::server::radius const _radius,
	sanguis::server::damage::unit const _damage,
	sanguis::server::damage::array const &_damage_values
)
:
	sanguis::server::entities::with_auras(
		fcppt::assign::make_container<
			sanguis::server::auras::container
		>(
			fcppt::make_unique_ptr<
				sanguis::server::auras::aoe_damage
			>(
				_team,
				_radius,
				_damage,
				_damage_values
			)
		)
		.move_container()
	),
	sanguis::server::entities::center_ghost()
{
}

sanguis::server::entities::projectiles::aoe_damage::~aoe_damage()
{
}

bool
sanguis::server::entities::projectiles::aoe_damage::dead() const
{
	return
		true;
}
