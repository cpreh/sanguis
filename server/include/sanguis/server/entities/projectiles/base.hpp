#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_BASE_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/with_id.hpp>
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

class base
:
	public virtual sanguis::server::entities::ifaces::with_team,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_links,
	public sanguis::server::entities::with_velocity
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base(
		sanguis::server::team,
		sanguis::server::entities::movement_speed,
		sanguis::load::model::path const &,
		sanguis::server::environment::load_context &,
		sanguis::server::entities::projectiles::life_time,
		sanguis::server::direction
	);

	~base()
	override;

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
	world_collision()
	override;

	virtual
	boost::logic::tribool
	can_collide_with_body(
		sanguis::server::entities::with_body const &
	) const
	override;

	void
	collision_with_body(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::collision::world::body_group
	collision_group() const
	override;

	virtual
	void
	do_damage(
		sanguis::server::entities::with_health &
	) = 0;

	sanguis::server::team const team_;

	sanguis::diff_timer life_timer_;
};

}
}
}
}

#endif
