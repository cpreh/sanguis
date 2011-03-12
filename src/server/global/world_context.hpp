#ifndef SANGUIS_SERVER_GLOBAL_WORLD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_WORLD_CONTEXT_HPP_INCLUDED

#include "world_context_fwd.hpp"
#include "context_fwd.hpp"
#include "../world/context.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace global
{

class world_context
:
	public world::context
{
	FCPPT_NONCOPYABLE(world_context)
public:
	explicit world_context(
		global::context &
	);

	~world_context();

	void
	transfer_entity(
		world_id destination,
		entities::unique_ptr,
		entities::insert_parameters const &
	);

	void
	send_to_player(
		player_id,
		messages::auto_ptr
	);

	void
	remove_player(
		player_id
	);
private:
	global::context &global_context_;
};

}
}
}

#endif
