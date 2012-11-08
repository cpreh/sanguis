#include <sanguis/server/speed.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/message_convert/speed.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/speed.hpp>


sanguis::messages::auto_ptr
sanguis::server::message_convert::speed(
	sanguis::server::entities::with_velocity const &_entity
)
{
	return
		sanguis::messages::create(
			sanguis::messages::speed(
				_entity.id(),
				_entity.speed().get()
			)
		);
}
