#include "health.hpp"
#include "../entities/entity.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/health.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::health(
	entities::entity const &e)
{
	return messages::create(
		messages::health(
			e.id(),
			e.health()
		)
	);
}
