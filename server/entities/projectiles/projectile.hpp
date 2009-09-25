#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include "indeterminate.hpp"
#include "life_time.hpp"
#include "../entity.hpp"
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
	public base
{
public:
	projectile_type::type
	ptype() const;
protected:
	projectile(
		projectile_type::type,
		team::type team,
		movement_speed,
		life_time,
		indeterminate::type
	);
	
	void
	on_update(
		time_type
	);
private:
	virtual entity_type::type
	type() const;

	bool
	invulnerable() const;

	server::team::type
	team() const;

	virtual boost::logic::tribool const 
	can_collide_with_entity(
		entity const &
	) const;

	void
	collision_entity_begin(
		entity &
	);

	messages::auto_ptr
	add_message() const;

	server::team::type const team_;
	projectile_type::type const ptype_;
	diff_clock diff_clock_;
	sge::time::timer life_timer_;
};

}
}
}
}

#endif
