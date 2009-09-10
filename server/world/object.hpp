#ifndef SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "context_ptr.hpp"
#include "environment_fwd.hpp"
#include "prop_container.hpp"
#include "../entities/container.hpp"
#include "../entities/auto_ptr.hpp"
#include "../environment_ptr.hpp"
#include "../exp_type.hpp"
#include "../../diff_clock.hpp"
#include "../../time_type.hpp"
#include <sge/collision/world_fwd.hpp>
#include <sge/collision/system_fwd.hpp>
#include <sge/time/timer.hpp>
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
	object(
		context_ptr const global_context_,
		sge::collision::system_ptr
	);

	~object();

	void
	update(
		time_type
	);
private:
	friend class environment;

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
	divide_exp(
		exp_type
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

	sge::collision::world_ptr const
	collision_world() const;

	// owns functions
	void
	send_entity_specific(
		entity_id,
		messages::auto_ptr
	);

	void
	send_player_specific(
		entity_id player_id,
		messages::auto_ptr
	);

	context_ptr const global_context_;

	sge::collision::world_ptr const collision_world_;

	diff_clock diff_clock_;

	sge::time::timer sight_range_timer_;

	entity_map entities_;

	prop_container props_;

	sge::signal::scoped_connection const
		collision_test_connection_,
		collision_connection_;
	
	server::environment::object_ptr const callbacks_;
};

}
}
}

#endif
