#include <sanguis/messages/base.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/rotate.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/message_convert/rotate.hpp>


sanguis::messages::unique_ptr
sanguis::server::message_convert::rotate(
	sanguis::server::entities::with_body const &_entity
)
{
	return
		sanguis::messages::create(
			sanguis::messages::rotate(
				_entity.id(),
				_entity.angle().get()
			)
		);
}
