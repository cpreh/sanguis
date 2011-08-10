#ifndef SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "object_fwd.hpp"
#include "../environment/object.hpp"
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		environment
	);
public:
	explicit environment(
		world::object &
	);

	~environment();

	void
	insert(
		entities::unique_ptr,
		entities::insert_parameters const &
	);

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

	collision::global_groups const &
	global_collision_groups() const;

	server::environment::load_context &
	load_context() const;
private:
	world::object &world_;
};

}
}
}

#endif
