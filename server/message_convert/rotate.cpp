#include "rotate.hpp"
#include "../entities/entity.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/rotate.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::rotate(
	entities::entity const &e)
{
	return messages::create(
		messages::rotate(
			e.id(),
			e.angle()
		)
	);
}
