#include <sanguis/server/message_convert/rotate.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/rotate.hpp>

sanguis::messages::auto_ptr
sanguis::server::message_convert::rotate(
	entities::with_body const &_entity
)
{
	return
		messages::create(
			messages::rotate(
				_entity.id(),
				_entity.angle().get()
			)
		);
}
