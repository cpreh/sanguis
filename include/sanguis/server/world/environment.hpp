#ifndef SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_description_fwd.hpp>
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
	)
	override;

	void
	weapon_changed(
		sanguis::entity_id,
		sanguis::optional_primary_weapon_type
	)
	override;

	void
	got_weapon(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::weapon_description const &
	)
	override;

	void
	remove_weapon(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::is_primary_weapon
	)
	override;

	void
	attacking_changed(
		sanguis::entity_id,
		bool is_attacking
	)
	override;

	void
	reloading_changed(
		sanguis::entity_id,
		bool is_reloading
	)
	override;

	void
	max_health_changed(
		sanguis::entity_id,
		sanguis::server::health
	)
	override;

	void
	exp_changed(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::server::exp
	)
	override;

	void
	level_changed(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::server::level
	)
	override;

	void
	pickup_chance(
		sanguis::server::pickup_probability,
		sanguis::server::center const &
	)
	override;

	void
	add_sight_range(
		sanguis::server::player_id,
		sanguis::entity_id target_id
	)
	override;

	void
	remove_sight_range(
		sanguis::server::player_id,
		sanguis::entity_id target_id
	)
	override;

	void
	remove_player(
		sanguis::server::player_id
	)
	override;

	void
	request_transfer(
		sanguis::entity_id
	)
	override;

	sge::projectile::world &
	collision_world() const
	override;

	sanguis::server::collision::global_groups const &
	global_collision_groups() const
	override;

	sanguis::server::environment::load_context &
	load_context() const
	override;
private:
	sanguis::server::world::object &world_;
};

}
}
}

#endif
