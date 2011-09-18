#include <sanguis/server/message_convert/move.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/messages/move.hpp>
#include <sanguis/messages/create.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sanguis::messages::auto_ptr
sanguis::server::message_convert::move(
	entities::with_velocity const &_entity
)
{
	return
		messages::create(
			messages::move(
				_entity.id(),
				_entity.center().get()
			)
		);
}
