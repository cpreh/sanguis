#ifndef SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "context_fwd.hpp"
#include "environment_fwd.hpp"
#include "entity_map.hpp"
#include "sight_range_map.hpp"
#include "../entities/unique_ptr.hpp"
#include "../entities/insert_parameters_fwd.hpp"
#include "../entities/base_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../collision/global_groups.hpp"
#include "../center.hpp"
#include "../console_fwd.hpp"
#include "../exp.hpp"
#include "../level.hpp"
#include "../health.hpp"
#include "../player_id.hpp"
#include "../probability.hpp"
#include "../string.hpp"
#include "../../diff_clock.hpp"
#include "../../time_delta_fwd.hpp"
#include "../../world_id.hpp"
#include "../../weapon_type.hpp"
#include "../../messages/auto_ptr.hpp"
#include <sanguis/creator/generator/result_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/time/timer.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

#include "../pickup_spawner.hpp"
#include "../waves/generator.hpp"

namespace sanguis
{
namespace server
{
namespace world
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		world::context &,
		server::environment::load_context &,
		server::console &,
		sanguis::creator::generator::result const &
	);

	~object();

	void
	update(
		sanguis::time_delta const &
	);

	void
	insert(
		entities::unique_ptr,
		entities::insert_parameters const &
	);

	server::environment::object &
	environment() const;
private:
	friend class environment;

	void
	weapon_changed(
		sanguis::entity_id,
		weapon_type::type
	);

	void
	got_weapon(
		server::player_id,
		sanguis::entity_id,
		weapon_type::type
	);

	void
	attacking_changed(
		sanguis::entity_id,
		bool is_attacking
	);

	void
	reloading_changed(
		sanguis::entity_id,
		bool is_reloading
	);

	void
	max_health_changed(
		sanguis::entity_id,
		server::health
	);

	void
	exp_changed(
		server::player_id,
		sanguis::entity_id,
		server::exp
	);

	void
	level_changed(
		server::player_id,
		sanguis::entity_id,
		server::level
	);

	void
	pickup_chance(
		server::probability spawn_chance,
		server::center const &
	);

	void
	request_transfer(
		sanguis::world_id,
		sanguis::entity_id,
		entities::insert_parameters const &
	);

	void
	add_sight_range(
		server::player_id,
		sanguis::entity_id target_id
	);

	void
	remove_sight_range(
		server::player_id,
		sanguis::entity_id target_id
	);

	void
	remove_player(
		server::player_id
	);

	sge::projectile::world &
	collision_world() const;

	server::collision::global_groups const &
	global_collision_groups() const;

	server::environment::load_context &
	load_context() const;

	// own functions
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

	void
	update_entity(
		entity_map::iterator,
		sanguis::time_delta const &,
		bool update_pos
	);

	world::context &global_context_;

	server::environment::load_context &load_context_;

	typedef fcppt::scoped_ptr<
		sge::projectile::world
	> collision_world_scoped_ptr;

	collision_world_scoped_ptr const collision_world_;

	server::collision::global_groups const collision_groups_;

	fcppt::signal::scoped_connection const collision_connection_;

	sight_range_map sight_ranges_;

	sanguis::diff_clock diff_clock_;

	sge::time::timer send_timer_;

	typedef fcppt::scoped_ptr<
		server::environment::object
	> environment_scoped_ptr;

	environment_scoped_ptr const environment_;

	entity_map entities_;

	server::pickup_spawner pickup_spawner_;

	waves::generator wave_gen_; // TODO: this doesn't belong here, only for testing!

	typedef fcppt::scoped_ptr<
		sge::projectile::body::object
	> collision_body_scoped_ptr;

	collision_body_scoped_ptr static_body_;
};

}
}
}

#endif
