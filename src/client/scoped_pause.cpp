#include <sanguis/client/scoped_pause.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/player_pause.hpp>
#include <sanguis/messages/player_unpause.hpp>


sanguis::client::scoped_pause::scoped_pause(
	sanguis::client::send_callback const &_send
)
:
	send_(
		_send
	)
{
	send_(
		*sanguis::messages::create(
			sanguis::messages::player_pause()
		)
	);
}

sanguis::client::scoped_pause::~scoped_pause()
{
	send_(
		*sanguis::messages::create(
			sanguis::messages::player_unpause()
		)
	);
}
