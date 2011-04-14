#include "send_available_perks.hpp"
#include "perks/list.hpp"
#include "entities/player.hpp"
#include "../messages/available_perks.hpp"
#include "../messages/create.hpp"
#include <fcppt/container/raw_vector_impl.hpp>

void
sanguis::server::send_available_perks(
	entities::player const &_player,
	server::unicast_callback const &_send
)
{
	perks::list const &list(
		_player.available_perks()
	);

	_send(
		_player.player_id(),
		messages::create(
			messages::available_perks(
				_player.id(),
				messages::types::enum_vector(
					list.begin(),
					list.end()
				)
			)
		)
	);
}
