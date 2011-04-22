#include "scoped_pause.hpp"
#include "../messages/create.hpp"
#include "../messages/player_pause.hpp"
#include "../messages/player_unpause.hpp"

sanguis::client::scoped_pause::scoped_pause(
	client::send_callback const &_send
)
:
	send_(_send)
{
	send_(
		messages::create(
			messages::player_pause()
		)
	);
}

sanguis::client::scoped_pause::~scoped_pause()
{
	send_(
		messages::create(
			messages::player_unpause()
		)
	);
}
