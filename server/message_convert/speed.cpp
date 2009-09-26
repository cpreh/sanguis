#include "speed.hpp"
#include "../entities/movable.hpp"
#include "../../messages/speed.hpp"
#include "../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>

sanguis::messages::auto_ptr
sanguis::server::message_convert::speed(
	entities::movable const &e
)
{
	return messages::create(
		messages::speed(
			e.id(),
			e.abs_speed()
		)
	);
}
