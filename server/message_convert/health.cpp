#include "health.hpp"
#include "../entities/with_health.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/health.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::health(
	entities::with_health const &e
)
{
	return messages::create(
		messages::health(
			e.id(),
			e.current_health()
		)
	);
}
