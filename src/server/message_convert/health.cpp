#include <sanguis/messages/base.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/health.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/message_convert/health.hpp>


sanguis::messages::unique_ptr
sanguis::server::message_convert::health(
	sanguis::server::entities::with_health const &_entity
)
{
	return
		sanguis::messages::create(
			sanguis::messages::health(
				_entity.id(),
				_entity.current_health().get()
			)
		);
}
