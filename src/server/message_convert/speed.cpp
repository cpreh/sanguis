#include "speed.hpp"
#include "../entities/with_velocity.hpp"
#include "../../messages/speed.hpp"
#include "../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

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
