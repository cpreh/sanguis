#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED

#include <sanguis/server/aoe_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/modified_array_fwd.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/simple.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::projectiles
{

class aoe_damage
:
	public sanguis::server::entities::with_auras,
	public sanguis::server::entities::simple,
	private sanguis::server::entities::center_ghost
{
	FCPPT_NONMOVABLE(
		aoe_damage
	);
public:
	aoe_damage(
		sanguis::server::team,
		sanguis::server::aoe,
		sanguis::server::damage::unit,
		sanguis::server::damage::modified_array const &
	);

	~aoe_damage()
	override;
private:
	[[nodiscard]]
	bool
	dead() const
	override;
};

}

#endif
