#ifndef SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "environment_fwd.hpp"
#include "prop_container.hpp"
#include "../entities/container.hpp"
#include "../entities/auto_ptr.hpp"
#include "../exp_type.hpp"
#include "../../time_type.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

class object {
	SGE_NONCOPYABLE(object)
public:
	object();

	~object();

	void
	update(
		time_type
	);

	void
	transfer(
		sever::entities::entity_auto_ptr
	);
private:
	friend class environment;

	// environment callbacks
	
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
	request_transfer(
		world_id,
		entity_id
	);

	void
	update_sight_range(
		net::id_type player_id,
		entity_id target_id
	);

	entities::entity & 
	insert(
		entities::auto_ptr
	);
/*

	void
	divide_exp(
		exp_type
	);
*/

	// owns functions
	void
	send_entity_specific(
		entity_id,
		messages::auto_ptr
	);


	server::entities::container entities_;

	prop_container props_;
};

}
}
}

#endif
