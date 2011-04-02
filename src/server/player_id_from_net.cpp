#include "player_id_from_net.hpp"

sanguis::server::player_id const
sanguis::server::player_id_from_net(
	sanguis::net::id const _id
)
{
	return
		server::player_id(
			_id.get()
		);
}
