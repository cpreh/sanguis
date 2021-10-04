#ifndef SANGUIS_SERVER_PLAYER_ID_FROM_NET_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_ID_FROM_NET_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <alda/net/id.hpp>


namespace sanguis::server
{

sanguis::server::player_id
player_id_from_net(
	alda::net::id
);

}

#endif
