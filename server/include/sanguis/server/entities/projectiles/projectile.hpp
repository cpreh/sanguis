#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include <sanguis/projectile_type.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/movement_speed_fwd.hpp>
#include <sanguis/server/entities/projectiles/base.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
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

class projectile
:
	public sanguis::server::entities::projectiles::base
{
	FCPPT_NONCOPYABLE(
		projectile
	);
protected:
	projectile(
		sanguis::projectile_type,
		sanguis::server::team,
		sanguis::server::entities::movement_speed,
		sanguis::server::environment::load_context &,
		sanguis::server::entities::projectiles::life_time,
		sanguis::server::direction
	);

	~projectile()
	override;

	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;
private:
	sanguis::projectile_type const projectile_type_;
};

}
}
}
}

#endif
