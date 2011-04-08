#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include "indeterminate.hpp"
#include "life_time.hpp"
#include "../body_velocity_combiner.hpp"
#include "../with_body_fwd.hpp"
#include "../with_dim.hpp"
#include "../with_health_fwd.hpp"
#include "../with_velocity.hpp"
#include "../movement_speed.hpp"
#include "../../dim.hpp"
#include "../../direction.hpp"
#include "../../../entity_type.hpp"
#include "../../../projectile_type.hpp"
#include "../../../time_type.hpp"
#include "../../../diff_clock.hpp"
#include "../../../messages/base.hpp"
#include <sge/time/timer.hpp>
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
	public with_dim,
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
	on_update(
		time_type
	);

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

	diff_clock diff_clock_;

	sge::time::timer life_timer_;
};

}
}
}
}

#endif
