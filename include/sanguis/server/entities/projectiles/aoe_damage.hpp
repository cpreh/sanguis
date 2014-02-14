#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_DAMAGE_HPP_INCLUDED

#include <sanguis/server/aoe_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/array_fwd.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>
#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class aoe_damage
:
	public sanguis::server::entities::with_auras,
	private sanguis::server::entities::center_ghost
{
	FCPPT_NONCOPYABLE(
		aoe_damage
	);
public:
	aoe_damage(
		sanguis::server::team,
		sanguis::server::aoe,
		sanguis::server::damage::unit,
		sanguis::server::damage::array const &
	);

	~aoe_damage();
private:
	bool
	dead() const
	override;
};

}
}
}
}

#endif
