#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_ROCKET_HPP_INCLUDED

#include <sanguis/server/aoe_fwd.hpp>
#include <sanguis/server/direction_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class rocket
:
	public sanguis::server::entities::projectiles::aoe_projectile
{
	FCPPT_NONCOPYABLE(
		rocket
	);
public:
	rocket(
		sanguis::server::environment::load_context &,
		sanguis::server::team,
		sanguis::server::damage::unit,
		sanguis::server::damage::modified_array const &,
		sanguis::server::aoe,
		sanguis::server::direction
	);

	~rocket()
	override;
private:
	void
	do_damage(
		sanguis::server::entities::with_health &
	)
	override;

	void
	remove_from_game()
	override;

	sanguis::server::damage::unit const damage_;

	sanguis::server::damage::modified_array const damage_modifiers_;
};

}
}
}
}

#endif
