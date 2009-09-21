#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/entity_fwd.hpp"
#include "../entities/insert_parameters_fwd.hpp"
#include "../player_id.hpp"
#include "../health_type.hpp"
#include "../exp_type.hpp"
#include "../../world_id.hpp"
#include "../../weapon_type.hpp"
#include "../../entity_id.hpp"
#include <sge/collision/world_fwd.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace environment
{

class object {
	SGE_NONCOPYABLE(object)
protected:
	object();
public:
	virtual entities::entity & 
	insert(
		entities::auto_ptr,
		entities::insert_parameters const &
	) = 0;

	virtual void
	weapon_changed(
		entity_id id,
		weapon_type::type
	) = 0;

	virtual void
	got_weapon(
		entity_id id,
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
		health_type
	) = 0;

	virtual void
	divide_exp(
		exp_type
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

	virtual sge::collision::world_ptr const
	collision_world() const = 0;

	virtual ~object();
};

}
}
}

#endif
