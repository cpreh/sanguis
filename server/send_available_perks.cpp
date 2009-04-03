#include "send_available_perks.hpp"
#include "perks/list.hpp"
#include "entities/player.hpp"
#include "../messages/available_perks.hpp"
#include "../messages/create.hpp"
#include <sge/container/raw_vector_impl.hpp>

void
sanguis::server::send_available_perks(
	entities::player &p,
	send_callback const &send)
{
	perks::list const &list(
		p.available_perks()
	);

	send(
		messages::create(
			messages::available_perks(
				p.id(),
				messages::types::enum_vector(
					list.begin(),
					list.end()
				)
			)
		)
	);
}
