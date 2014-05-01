#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/collision/result_fwd.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>


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
	public virtual sanguis::server::entities::ifaces::with_team,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_links,
	public sanguis::server::entities::with_velocity
{
	FCPPT_NONCOPYABLE(
		projectile
	);
protected:
	projectile(
		sanguis::projectile_type,
		sanguis::server::team,
		sanguis::server::entities::movement_speed,
		sanguis::server::model_name const &,
		sanguis::server::environment::load_context &,
		sanguis::server::entities::projectiles::life_time,
		sanguis::server::direction
	);

	~projectile();

	void
	expire();

	sanguis::server::team
	team() const
	override;
private:
	bool
	dead() const
	override;

	void
	on_world_collision(
		sanguis::server::collision::result const &
	)
	override;

	virtual
	boost::logic::tribool const
	can_collide_with_body(
		sanguis::server::entities::with_body const &
	) const
	override;

	void
	collision_with_body(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::collision::world::group_field const
	collision_groups() const
	override;

	virtual
	void
	do_damage(
		sanguis::server::entities::with_health &
	) = 0;

	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	sanguis::server::team const team_;

	sanguis::projectile_type const projectile_type_;

	sanguis::diff_timer life_timer_;
};

}
}
}
}

#endif
