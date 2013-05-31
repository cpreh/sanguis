#include <sanguis/messages/create.hpp>
#include <sanguis/messages/move.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/message_convert/move.hpp>


sanguis::messages::unique_ptr
sanguis::server::message_convert::move(
	sanguis::server::entities::with_velocity const &_entity
)
{
	return
		sanguis::messages::create(
			sanguis::messages::move(
				_entity.id(),
				_entity.center().get()
			)
		);
}
