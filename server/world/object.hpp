#ifndef SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "context_ptr.hpp"
#include "environment_fwd.hpp"
#include "prop_container.hpp"
#include "entity_map.hpp"
#include "sight_range_map.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/insert_parameters_fwd.hpp"
#include "../environment/object_ptr.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../exp_type.hpp"
#include "../health_type.hpp"
#include "../player_id.hpp"
#include "../dim_type.hpp"
#include "../string.hpp"
#include "../../diff_clock.hpp"
#include "../../time_type.hpp"
#include "../../world_id.hpp"
#include "../../weapon_type.hpp"
#include "../../messages/auto_ptr.hpp"
#include <sge/collision/world_fwd.hpp>
#include <sge/collision/system_fwd.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/time/timer.hpp>
#include <sge/noncopyable.hpp>

#include "../waves/generator.hpp"

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
		sge::collision::system_ptr,
		server::environment::load_context_ptr
	);

	~object();

	void
	update(
		time_type
	);

	entities::entity & 
	insert(
		entities::auto_ptr,
		entities::insert_parameters const &
	);

	server::environment::object_ptr const
	environment() const;
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
		entity_id,
		entities::insert_parameters const &
	);

	void
	add_sight_range(
		player_id,
		entity_id target_id
	);

	void
	remove_sight_range(
		player_id,
		entity_id target_id
	);
	void
	remove_player(
		player_id
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
		player_id,
		messages::auto_ptr
	);

	context_ptr const global_context_;

	server::environment::load_context_ptr const load_context_;

	sge::collision::world_ptr const collision_world_;

	diff_clock diff_clock_;

	sge::time::timer send_timer_;

	entity_map entities_;

	sight_range_map sight_ranges_;

	prop_container props_;

	sge::signal::scoped_connection const
		collision_connection_begin_,
		collision_connection_end_,
		collision_connection_test_;
	
	server::environment::object_ptr const environment_;

	waves::generator wave_gen_; // TODO: this doesn't belong here, only for testing!
};

}
}
}

#endif
