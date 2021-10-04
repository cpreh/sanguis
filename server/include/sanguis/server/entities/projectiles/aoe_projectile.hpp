#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_AOE_PROJECTILE_HPP_INCLUDED

#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/direction_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/projectiles/base.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::projectiles
{

class aoe_projectile
:
	public sanguis::server::entities::projectiles::base
{
	FCPPT_NONMOVABLE(
		aoe_projectile
	);
protected:
	aoe_projectile(
		sanguis::aoe_projectile_type,
		sanguis::server::team,
		sanguis::server::entities::movement_speed,
		sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
		sanguis::server::entities::projectiles::life_time,
		sanguis::server::aoe,
		sanguis::server::direction
	);

	~aoe_projectile()
	override;

	[[nodiscard]]
	sanguis::server::aoe
	aoe() const;
private:
	[[nodiscard]]
	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id,
		sanguis::collision::world::created
	) const
	override;

	sanguis::aoe_projectile_type const type_;

	sanguis::server::aoe const aoe_;
};

}

#endif
