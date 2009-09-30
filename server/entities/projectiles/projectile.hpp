#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include "indeterminate.hpp"
#include "life_time.hpp"
#include "../movable.hpp"
#include "../with_dim.hpp"
#include "../with_health_fwd.hpp"
#include "../movement_speed.hpp"
#include "../../dim_type.hpp"
#include "../../space_unit.hpp"
#include "../../../entity_type.hpp"
#include "../../../projectile_type.hpp"
#include "../../../time_type.hpp"
#include "../../../diff_clock.hpp"
#include "../../../messages/base.hpp"
#include <sge/time/timer.hpp>

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
	public movable,
	public with_dim
{
public:
	projectile_type::type
	ptype() const;
protected:
	projectile(
		projectile_type::type,
		team::type team,
		entities::movement_speed,
		dim_type const &,
		life_time,
		space_unit direction,
		indeterminate::type
	);
	
	void
	on_update(
		time_type
	);

	void
	die();

	server::team::type
	team() const;
private:
	virtual void
	on_die();

	bool
	dead() const;

	bool
	invulnerable() const;

	virtual entity_type::type
	type() const;

	virtual boost::logic::tribool const 
	can_collide_with_entity(
		base const &
	) const;

	void
	collision_entity_begin(
		base &
	);

	virtual void
	do_damage(
		with_health &
	) = 0;

	messages::auto_ptr
	add_message() const;

	server::team::type const team_;

	entity_type::type const type_;

	projectile_type::type const ptype_;

	diff_clock diff_clock_;

	sge::time::timer life_timer_;
};

}
}
}
}

#endif
