#include <sanguis/server/net_id_from_player.hpp>
#include <sanguis/server/player_id.hpp>
#include <alda/net/id.hpp>


alda::net::id
sanguis::server::net_id_from_player(
	sanguis::server::player_id const _id
)
{
	return
		alda::net::id(
			_id.get()
		);
}
