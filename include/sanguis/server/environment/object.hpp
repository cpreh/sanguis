#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED

#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/probability.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/entity_id.hpp>
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
	virtual void
	insert(
		entities::unique_ptr,
		entities::insert_parameters const &
	) = 0;

	virtual void
	weapon_changed(
		entity_id id,
		weapon_type::type
	) = 0;

	virtual void
	got_weapon(
		player_id,
		entity_id,
		weapon_type::type
	) = 0;

	virtual void
	attacking_changed(
		entity_id,
		bool is_attacking
	) = 0;

	virtual void
	reloading_changed(
		entity_id,
		bool is_reloading
	) = 0;

	virtual void
	max_health_changed(
		entity_id,
		server::health
	) = 0;

	virtual void
	exp_changed(
		server::player_id,
		sanguis::entity_id,
		server::exp
	) = 0;

	virtual void
	level_changed(
		player_id,
		entity_id,
		server::level
	) = 0;

	virtual void
	pickup_chance(
		server::probability spawn_chance,
		server::center const &
	) = 0;

	virtual void
	request_transfer(
		world_id,
		entity_id,
		entities::insert_parameters const &
	) = 0;

	virtual void
	add_sight_range(
		player_id,
		entity_id
	) = 0;

	virtual void
	remove_sight_range(
		player_id,
		entity_id
	) = 0;

	virtual void
	remove_player(
		player_id
	) = 0;

	virtual sge::projectile::world &
	collision_world() const = 0;

	virtual collision::global_groups const &
	global_collision_groups() const = 0;

	virtual environment::load_context &
	load_context() const = 0;

	virtual ~object();
};

}
}
}

#endif
