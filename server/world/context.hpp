#ifndef SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED

#include "context_fwd.hpp"
#include "../player_id.hpp"
#include "../entities/auto_tpr.hpp"
#include "../../world_id.hpp"
#include "../../messages/auto_ptr.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

class context {
	SGE_NONCOPYABLE(context)
public:
	virtual void
	transfer_entity(
		world_id destination,
		entities::auto_ptr
	) = 0;

	virtual void
	send_to_player(
		player_id,
		messages::auto_ptr
	) = 0;

	virtual ~context();
};

}
}
}

#endif
