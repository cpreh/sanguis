#include "stop_reloading.hpp"
#include "../entities/entity.hpp"
#include "../../messages/create.hpp"
#include "../../messages/base.hpp"
#include "../../messages/stop_reloading.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::stop_reloading(
	entities::entity const &e)
{
	return messages::create(
		messages::stop_reloading(
			e.id()
		)
	);
}
