#include "max_health.hpp"
#include "../entities/entity.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/max_health.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::max_health(
	entities::entity const &e)
{
	return messages::create(
		messages::max_health(
			e.id(),
			e.max_health()
		)
	);
}
