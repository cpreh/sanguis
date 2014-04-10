#ifndef SANGUIS_SERVER_NET_ID_FROM_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_NET_ID_FROM_PLAYER_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <alda/net/id.hpp>


namespace sanguis
{
namespace server
{

alda::net::id const
net_id_from_player(
	sanguis::server::player_id
);

}
}

#endif
