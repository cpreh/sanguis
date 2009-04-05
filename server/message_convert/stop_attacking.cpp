#include "stop_attacking.hpp"
#include "../entities/entity.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/stop_attacking.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::stop_attacking(
	entities::entity const &e)
{
	return messages::create(
		messages::stop_attacking(
			e.id()
		)
	);
}
