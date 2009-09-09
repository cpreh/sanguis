#ifndef SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "../environment/object.hpp"

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
public:
	environment();

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

	entities::entity & 
	insert(
		entities::auto_ptr
	);
private:
	
};

}
}
}

#endif
