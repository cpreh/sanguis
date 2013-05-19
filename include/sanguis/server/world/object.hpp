#ifndef SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/result_fwd.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/size.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/pickup_spawner.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/collision/global_groups.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/waves/generator.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/environment_fwd.hpp>
#include <sanguis/server/world/entity_map.hpp>
#include <sanguis/server/world/object_fwd.hpp>
#include <sanguis/server/world/sight_range_map.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/body/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>



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
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::world_id,
		sanguis::server::world::context &,
		sanguis::server::environment::load_context &,
		sanguis::server::console &,
		sanguis::creator::result const &
	);

	~object();

	void
	update();

	void
	insert(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	);

	sanguis::server::environment::object &
	environment() const;
private:
	friend class environment;

	void
	weapon_changed(
		sanguis::entity_id,
		sanguis::weapon_type
	);

	void
	got_weapon(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::weapon_type
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
		sanguis::server::health
	);

	void
	exp_changed(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::server::exp
	);

	void
	level_changed(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::server::level
	);

	void
	pickup_chance(
		sanguis::server::pickup_probability,
		sanguis::server::center const &
	);

	void
	request_transfer(
		sanguis::world_id,
		sanguis::entity_id,
		sanguis::server::entities::insert_parameters const &
	);

	void
	add_sight_range(
		sanguis::server::player_id,
		sanguis::entity_id target_id
	);

	void
	remove_sight_range(
		sanguis::server::player_id,
		sanguis::entity_id target_id
	);

	void
	remove_player(
		sanguis::server::player_id
	);

	sge::projectile::world &
	collision_world() const;

	sanguis::server::collision::global_groups const &
	global_collision_groups() const;

	sanguis::server::environment::load_context &
	load_context() const;

	// own functions
	void
	send_entity_specific(
		sanguis::entity_id,
		sanguis::messages::base const &
	);

	void
	send_player_specific(
		sanguis::server::player_id,
		sanguis::messages::base const &
	);

	void
	update_entity(
		sanguis::server::world::entity_map::iterator,
		bool update_pos
	);

	sanguis::world_id const id_;

	sanguis::creator::seed const seed_;

	sanguis::creator::name const generator_name_;

	sanguis::creator::size const size_;

	sanguis::server::world::context &global_context_;

	sanguis::server::environment::load_context &load_context_;

	typedef fcppt::scoped_ptr<
		sge::projectile::world
	> collision_world_scoped_ptr;

	collision_world_scoped_ptr const collision_world_;

	sanguis::server::collision::global_groups const collision_groups_;

	fcppt::signal::scoped_connection const collision_connection_;

	sight_range_map sight_ranges_;

	sanguis::diff_timer projectile_timer_;

	sanguis::timer send_timer_;

	typedef fcppt::scoped_ptr<
		sanguis::server::environment::object
	> environment_scoped_ptr;

	environment_scoped_ptr const environment_;

	entity_map entities_;

	sanguis::server::pickup_spawner pickup_spawner_;

	sanguis::server::waves::generator wave_gen_; // TODO: this doesn't belong here, only for testing!

	typedef fcppt::scoped_ptr<
		sge::projectile::body::object
	> collision_body_scoped_ptr;

	collision_body_scoped_ptr const static_body_;

	typedef fcppt::scoped_ptr<
		sge::projectile::body::scoped
	> scoped_static_body_ptr;

	scoped_static_body_ptr const scoped_static_body_;
};

}
}
}

#endif
