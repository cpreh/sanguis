#ifndef SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/server/world/object_fwd.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/environment_fwd.hpp>
#include <sanguis/server/world/entity_map.hpp>
#include <sanguis/server/world/sight_range_map.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/collision/global_groups.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/probability.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/result_fwd.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/math/dim/object_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

#include <sanguis/server/pickup_spawner.hpp>
#include <sanguis/server/waves/generator.hpp>

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
		world::context &,
		server::environment::load_context &,
		sge::charconv::system &,
		server::console &,
		sanguis::creator::generator::result const &
	);

	~object();

	void
	update();

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
		messages::base const &
	);

	void
	send_player_specific(
		player_id,
		messages::base const &
	);

	void
	update_entity(
		entity_map::iterator,
		bool update_pos
	);

	sanguis::world_id const id_;

	sanguis::creator::generator::seed const seed_;

	sanguis::creator::generator::name const generator_name_;

	sanguis::creator::generator::size const size_;

	world::context &global_context_;

	server::environment::load_context &load_context_;

	sge::charconv::system &charconv_system_;

	typedef fcppt::scoped_ptr<
		sge::projectile::world
	> collision_world_scoped_ptr;

	collision_world_scoped_ptr const collision_world_;

	server::collision::global_groups const collision_groups_;

	fcppt::signal::scoped_connection const collision_connection_;

	sight_range_map sight_ranges_;

	sanguis::diff_timer projectile_timer_;

	sanguis::timer send_timer_;

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
