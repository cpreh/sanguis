#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include "indeterminate.hpp"
#include "life_time.hpp"
#include "../body_velocity_combiner.hpp"
#include "../with_body.hpp"
#include "../with_health_fwd.hpp"
#include "../with_velocity.hpp"
#include "../movement_speed.hpp"
#include "../../dim.hpp"
#include "../../direction.hpp"
#include "../../../diff_clock_fwd.hpp"
#include "../../../diff_timer.hpp"
#include "../../../entity_type.hpp"
#include "../../../projectile_type.hpp"
#include "../../../messages/base.hpp"
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
