#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/entity_type_fwd.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/collision/result_fwd.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/projectiles/indeterminate_fwd.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
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
	private sanguis::server::entities::body_velocity_combiner,
	public sanguis::server::entities::with_body,
	public sanguis::server::entities::with_velocity
{
	FCPPT_NONCOPYABLE(
		projectile
	);
public:
	sanguis::projectile_type
	ptype() const;
protected:
	projectile(
		sanguis::diff_clock const &,
		sanguis::projectile_type,
		sanguis::server::team,
		sanguis::server::entities::movement_speed,
		sanguis::server::dim const &,
		sanguis::server::entities::projectiles::life_time,
		sanguis::server::direction,
		sanguis::server::entities::projectiles::indeterminate
	);

	~projectile();

	void
	expire();

	sanguis::server::team
	team() const;
private:
	bool
	server_only() const;

	bool
	dead() const;

	void
	world_collision(
		sanguis::server::collision::result const &
	);

	virtual
	sanguis::entity_type
	type() const;

	virtual
	boost::logic::tribool const
	can_collide_with_body(
		sanguis::server::entities::with_body const &
	) const;

	void
	collision_with_body(
		sanguis::server::entities::with_body &
	);

	virtual
	void
	do_damage(
		sanguis::server::entities::with_health &
	) = 0;

	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const;

	sanguis::server::team const team_;

	bool const server_only_;

	sanguis::projectile_type const ptype_;

	sanguis::diff_timer life_timer_;
};

}
}
}
}

#endif
