#ifndef SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "object_fwd.hpp"
#include "../environment/object.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

class environment
:
	public server::environment::object
{
	SGE_NONCOPYABLE(environment)
public:
	explicit environment(
		world::object &
	);

	~environment();

	void
	weapon_changed(
		entity_id id,
		weapon_type::type
	);

	void
	got_weapon(
		entity_id id,
		weapon_type::type
	);

	void
	attacking_changed(
		entity_id,
		bool is_attacking
	);

	void
	reloading_changed(
		entity_id,
		bool is_reloading
	);

	void
	max_health_changed(
		entity_id,
		health_type
	);
	
	void
	remove_player(
		player_id
	);

	entities::entity & 
	insert(
		entities::auto_ptr
	);

	sge::collision::world_ptr const
	collision_world() const;
private:
	world::object &world_;	
};

}
}
}

#endif
