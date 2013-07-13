#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED

#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
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
		sanguis::diff_clock const &,
		sanguis::aoe_projectile_type,
		sanguis::server::team,
		sanguis::server::entities::movement_speed,
		sanguis::server::environment::load_context &,
		sanguis::server::entities::projectiles::life_time,
		sanguis::server::radius,
		sanguis::server::direction
	);

	~aoe_projectile();

	sanguis::server::radius const
	aoe() const;
private:
	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const;

	sanguis::aoe_projectile_type const type_;

	sanguis::server::radius const aoe_;
};

}
}
}
}

#endif
