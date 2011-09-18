#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include <sanguis/server/entities/projectiles/indeterminate.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/entity_type.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/messages/base.hpp>
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
	private body_velocity_combiner,
	public with_body,
	public with_velocity
{
	FCPPT_NONCOPYABLE(
		projectile
	);
public:
	projectile_type::type
	ptype() const;
protected:
	projectile(
		sanguis::diff_clock const &,
		projectile_type::type,
		team::type team,
		entities::movement_speed,
		server::dim const &,
		projectiles::life_time,
		server::direction,
		indeterminate::type
	);

	~projectile();

	void
	expire();

	server::team::type
	team() const;
private:
	bool
	server_only() const;

	bool
	dead() const;

	virtual entity_type::type
	type() const;

	virtual boost::logic::tribool const
	can_collide_with_body(
		entities::with_body const &
	) const;

	void
	collision_with_body(
		entities::with_body &
	);

	virtual void
	do_damage(
		with_health &
	) = 0;

	messages::auto_ptr
	add_message(
		player_id
	) const;

	server::team::type const team_;

	bool const server_only_;

	projectile_type::type const ptype_;

	sanguis::diff_timer life_timer_;
};

}
}
}
}

#endif
