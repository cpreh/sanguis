#include "move.hpp"
#include "../entities/with_dim.hpp"
#include "../../messages/move.hpp"
#include "../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>

sanguis::messages::auto_ptr
sanguis::server::message_convert::move(
	entities::with_dim const &e
)
{
	return messages::create(
		messages::move(
			e.id(),
			e.pos()
		)
	);
}
