#include <sanguis/server/message_convert/speed.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/messages/speed.hpp>
#include <sanguis/messages/create.hpp>
#include <fcppt/math/vector/object_impl.hpp>

sanguis::messages::auto_ptr
sanguis::server::message_convert::speed(
	entities::with_velocity const &_entity
)
{
	return
		messages::create(
			messages::speed(
				_entity.id(),
				_entity.abs_speed().get()
			)
		);
}
