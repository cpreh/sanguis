#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PROJECTILE_HPP_INCLUDED

#include "indeterminate.hpp"
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
	typedef sge::optional<
		time_type
	> optional_life_time;

	projectile(
		projectile_type::type,
		server::environment::object_ptr,
		pos_type const &center,
		space_unit angle,
		team::type team,
		property_map const &,
		dim_type const &dim,
		optional_life_time const &,
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
	collision_entity(
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
	sge::time::timer lifetime;
};

}
}
}
}

#endif
