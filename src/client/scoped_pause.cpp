#include <sanguis/client/scoped_pause.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/player_pause.hpp>
#include <sanguis/messages/player_unpause.hpp>

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
