#include <sanguis/server/message_convert/health.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/health.hpp>

sanguis::messages::auto_ptr
sanguis::server::message_convert::health(
	entities::with_health const &_entity
)
{
	return
		messages::create(
			messages::health(
				_entity.id(),
				_entity.current_health().get()
			)
		);
}
