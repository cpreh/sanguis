#include "start_reloading.hpp"
#include "../entities/entity.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/start_reloading.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::start_reloading(
	entities::entity const &e)
{
	return messages::create(
		messages::start_reloading(
			e.id()
		)
	);
}
