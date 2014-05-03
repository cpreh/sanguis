#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aoe_damage.hpp>
#include <sanguis/server/auras/create_callback_container.hpp>
#include <sanguis/server/damage/array_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::entities::projectiles::aoe_damage::aoe_damage(
	sanguis::server::team const _team,
	sanguis::server::aoe const _aoe,
	sanguis::server::damage::unit const _damage,
	sanguis::server::damage::array const &_damage_values
)
:
	sanguis::server::entities::with_auras(
		sanguis::server::auras::create_callback_container{
			[
				_team,
				_aoe,
				_damage,
				_damage_values
			](
				sanguis::diff_clock const &
			)
			{
				return
					fcppt::make_unique_ptr<
						sanguis::server::auras::aoe_damage
					>(
						_team,
						_aoe,
						_damage,
						_damage_values
					);
			}
		}
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
