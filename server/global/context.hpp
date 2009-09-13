#ifndef SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED

#include "context_fwd.hpp"
#include "player_map.hpp"
#include "world_context_fwd.hpp"
#include "../world/map.hpp"
#include "../../world_id.hpp"
#include "../../messages/auto_ptr.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace global
{

class context {
	SGE_NONCOPYABLE(context)
public:
	context(
		unicast_callback const &,
		sge::collision::system_ptr
	);

	~context();

	void
	insert_player(
		world_id,
		player_id,
		string const &name
	);

	void
	player_target(
		player_id,
		pos_type const &
	);

	void
	player_change_weapon(
		player_id,
		weapon_type::type
	);

	void
	player_angle(
		player_id,
		space_unit
	);

	void
	player_change_shooting(
		player_id,
		bool shooting
	);

	void
	player_choose_perk(
		player_id,
		perk_type::type
	);

	void
	update(
		time_type
	);
private:
	friend class world_context;

	// callbacks for world

	void
	send_to_player(
		world_id,
		messages::auto_ptr
	);

	void
	remove_player(
		player_id
	);

	void
	transfer_entity(
		world_id destination,
		entities::auto_ptr
	);

	world::map worlds_;
	player_map players_;
};

}
}
}

#endif
