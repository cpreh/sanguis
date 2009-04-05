#include "start_attacking.hpp"
#include "../entities/entity.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/start_attacking.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::start_attacking(
	entities::entity const &e)
{
	return messages::create(
		messages::start_attacking(
			e.id()
		)
	);
}
