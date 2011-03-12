#ifndef SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONTEXT_HPP_INCLUDED

#include "context_fwd.hpp"
#include "../player_id.hpp"
#include "../entities/unique_ptr.hpp"
#include "../entities/insert_parameters_fwd.hpp"
#include "../../world_id.hpp"
#include "../../messages/auto_ptr.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

class context
{
	FCPPT_NONCOPYABLE(context)
protected:
	context();
public:
	virtual void
	transfer_entity(
		world_id destination,
		entities::unique_ptr,
		entities::insert_parameters const &
	) = 0;

	virtual void
	send_to_player(
		player_id,
		messages::auto_ptr
	) = 0;

	virtual void
	remove_player(
		player_id
	) = 0;

	virtual ~context();
};

}
}
}

#endif
