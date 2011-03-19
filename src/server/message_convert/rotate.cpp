#include "rotate.hpp"
#include "../entities/base.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/rotate.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::rotate(
	entities::base const &_entity
)
{
	return
		messages::create(
			messages::rotate(
				_entity.id(),
				_entity.angle()
			)
		);
}
