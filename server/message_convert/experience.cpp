#include "experience.hpp"
#include "../entities/player.hpp"
#include "../../messages/base.hpp"
#include "../../messages/create.hpp"
#include "../../messages/experience.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert::experience(
	entities::player const &p)
{
	return messages::create(
		messages::experience(
			p.id(),
			p.exp()
		)
	);
}
