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
#include <sge/optional_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

class projectile : public entity {
public:
	projectile_type::type ptype() const;
protected:
	projectile(
		projectile_type::type,
		server::environment::load_context_ptr,
		team::type team,
		property_map const &,
		dim_type const &dim,
		life_time,
		indeterminate::type
	);
	
	void
	update(
		time_type
	);
private:
	virtual boost::logic::tribool const 
	can_collide_with_entity(
		entity const &
	) const;
	
	void
	collision_entity_begin(
		entity &
	);

	virtual void
	do_damage(
		entity &
	) = 0;

	messages::auto_ptr
	add_message() const;

	projectile_type::type const ptype_;
	diff_clock diff_clock_;
	sge::time::timer life_timer_;
};

}
}
}
}

#endif
