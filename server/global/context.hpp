#ifndef SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_CONTEXT_HPP_INCLUDED

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
	explicit context(
		unicast_callback const &
	);

	~context();

	void
	insert_player(
		world_id,
		player_id,
		string const &name
	);

	void
	choose_perk(
		player_id,
		perk_type::type
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
