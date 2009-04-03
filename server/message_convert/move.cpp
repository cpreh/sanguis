#include "move.hpp"
#include "../../messages/move.hpp"
#include "../../messages/create.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::move(
	entities::entity const &e)
{
	return messages::create(
		messages::move(
			e.id(),
			e.pos()
		)
	);
}
