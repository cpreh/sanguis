#ifndef SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_base_ref_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/world/environment_fwd.hpp>
#include <sanguis/server/world/object_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class environment
:
	public sanguis::server::environment::object
{
	FCPPT_NONCOPYABLE(
		environment
	);
public:
	explicit
	environment(
		sanguis::server::world::object &
	);

	~environment();

	sanguis::server::entities::optional_base_ref const
	insert(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	);

	void
	weapon_changed(
		sanguis::entity_id,
		sanguis::optional_primary_weapon_type
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

	void
	request_transfer(
		sanguis::entity_id
	);

	sge::projectile::world &
	collision_world() const;

	sanguis::server::collision::global_groups const &
	global_collision_groups() const;

	sanguis::server::environment::load_context &
	load_context() const;
private:
	sanguis::server::world::object &world_;
};

}
}
}

#endif
