#include "move.hpp"
#include "../entities/with_dim.hpp"
#include "../../messages/move.hpp"
#include "../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::messages::auto_ptr
sanguis::server::message_convert::move(
	entities::with_dim const &_entity
)
{
	return
		messages::create(
			messages::move(
				_entity.id(),
				_entity.pos().get()
			)
		);
}
