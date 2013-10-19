#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED

#include <sanguis/aura_type_fwd.hpp>
#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/entity_id_fwd.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_base_ref_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
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
	sanguis::server::entities::optional_base_ref const
	insert(
		sanguis::server::entities::unique_ptr &&,
		sanguis::server::entities::insert_parameters const &
	) = 0;

	virtual
	void
	add_aura(
		sanguis::entity_id,
		sanguis::aura_type
	) = 0;

	virtual
	void
	add_buff(
		sanguis::entity_id,
		sanguis::buff_type
	) = 0;

	virtual
	void
	remove_buff(
		sanguis::entity_id,
		sanguis::buff_type
	) = 0;

	virtual
	void
	weapon_changed(
		sanguis::entity_id,
		sanguis::optional_primary_weapon_type
	) = 0;

	virtual
	void
	got_weapon(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::weapon_description const &
	) = 0;

	virtual
	void
	remove_weapon(
		sanguis::server::player_id,
		sanguis::entity_id,
		sanguis::is_primary_weapon
	) = 0;

	virtual
	void
	angle_changed(
		sanguis::entity_id,
		sanguis::server::angle
	) = 0;

	virtual
	void
	center_changed(
		sanguis::entity_id,
		sanguis::server::center
	) = 0;

	virtual
	void
	speed_changed(
		sanguis::entity_id,
		sanguis::server::speed
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
	health_changed(
		sanguis::entity_id,
		sanguis::server::health
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
		sanguis::server::entities::enemies::difficulty,
		sanguis::server::center const &
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
	void
	request_transfer(
		sanguis::entity_id
	) = 0;

	virtual
	sanguis::collision::world::object &
	collision_world() const = 0;

	virtual
	sanguis::creator::grid const &
	grid() const = 0;

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
