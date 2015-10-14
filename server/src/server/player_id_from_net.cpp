#include <sanguis/server/player_id.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <alda/net/id.hpp>


sanguis::server::player_id
sanguis::server::player_id_from_net(
	alda::net::id const _id
)
{
	return
		sanguis::server::player_id(
			_id.get()
		);
}
