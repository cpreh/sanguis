#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/entity_fwd.hpp"
#include "../../weapon_type.hpp"
#include "../../entity_id.hpp"
#include <sge/collision/world_fwd.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace environment
{

class object {
	SGE_NONCOPYABLE(object)
public:
	virtual void
	weapon_changed(
		entity_id id,
		weapon_type::type
	) = 0;

	virtual void
	got_weapon(
		entity_id id,
		weapon_type::type
	) = 0;

	virtual void
	attacking_changed(
		entity_id,
		bool is_attacking
	) = 0;

	virtual void
	reloading_changed(
		entity_id,
		bool is_reloading
	) = 0;

	virtual void
	max_health_changed(
		entity_id,
		health_type
	) = 0;

	virtual entities::entity & 
	insert(
		entities::auto_ptr
	) = 0;

	virtual sge::collision::world_ptr const
	collision_world() const = 0;

	virtual ~object();
};

}
}
}

#endif
