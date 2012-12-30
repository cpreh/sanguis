#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace environment
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	object();
public:
	virtual
	void
	insert(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	) = 0;

	virtual
	void
	weapon_changed(
		sanguis::entity_id,
		sanguis::weapon_type
	) = 0;

	virtual
	void
	got_weapon(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::weapon_type
	) = 0;

	virtual
	void
	attacking_changed(
		sanguis::entity_id,
		bool is_attacking
	) = 0;

	virtual
	void
	reloading_changed(
		sanguis::entity_id,
		bool is_reloading
	) = 0;

	virtual
	void
	max_health_changed(
		sanguis::entity_id,
		sanguis::server::health
	) = 0;

	virtual
	void
	exp_changed(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::server::exp
	) = 0;

	virtual
	void
	level_changed(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::server::level
	) = 0;

	virtual
	void
	pickup_chance(
		sanguis::server::pickup_probability,
		sanguis::server::center const &
	) = 0;

	virtual
	void
	request_transfer(
		sanguis::world_id,
		sanguis::entity_id,
		sanguis::server::entities::insert_parameters const &
	) = 0;

	virtual
	void
	add_sight_range(
		sanguis::server::player_id,
		sanguis::entity_id
	) = 0;

	virtual
	void
	remove_sight_range(
		sanguis::server::player_id,
		sanguis::entity_id
	) = 0;

	virtual
	void
	remove_player(
		sanguis::server::player_id
	) = 0;

	virtual
	sge::projectile::world &
	collision_world() const = 0;

	virtual
	sanguis::server::collision::global_groups const &
	global_collision_groups() const = 0;

	virtual
	sanguis::server::environment::load_context &
	load_context() const = 0;

	virtual
	~object();
};

}
}
}

#endif
