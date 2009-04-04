#include "remove.hpp"
#include "../entities/entity.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/remove.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::remove(
	entities::entity const &e)
{
	return messages::create(
		messages::remove(
			e.id()
		)
	);
}
