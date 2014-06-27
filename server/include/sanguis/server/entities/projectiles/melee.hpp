#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_MELEE_HPP_INCLUDED

#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/modified_array_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class melee
:
	public sanguis::server::entities::projectiles::aoe_damage
{
	FCPPT_NONCOPYABLE(
		melee
	);
public:
	melee(
		sanguis::server::team,
		sanguis::server::damage::unit,
		sanguis::server::damage::modified_array const &
	);

	~melee()
	override;
};

}
}
}
}

#endif
