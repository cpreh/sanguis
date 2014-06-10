#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED

#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/direction_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
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

class aoe_projectile
:
	public sanguis::server::entities::projectiles::projectile
{
	FCPPT_NONCOPYABLE(
		aoe_projectile
	);
protected:
	aoe_projectile(
		sanguis::aoe_projectile_type,
		sanguis::server::team,
		sanguis::server::entities::movement_speed,
		sanguis::server::environment::load_context &,
		sanguis::server::entities::projectiles::life_time,
		sanguis::server::aoe,
		sanguis::server::direction
	);

	~aoe_projectile()
	override;

	sanguis::server::aoe const
	aoe() const;
private:
	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	sanguis::aoe_projectile_type const type_;

	sanguis::server::aoe const aoe_;
};

}
}
}
}

#endif
