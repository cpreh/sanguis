#include "level_up.hpp"
#include "../entities/player.hpp"
#include "../../messages/create.hpp"
#include "../../messages/level_up.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::level_up(
	entities::player const &p)
{
	return messages::create(
		messages::level_up(
			p.id(),
			p.level()
		)
	);
}
