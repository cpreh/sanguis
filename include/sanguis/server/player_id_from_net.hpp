#ifndef SANGUIS_SERVER_PLAYER_ID_FROM_NET_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_ID_FROM_NET_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/net/id.hpp>

namespace sanguis
{
namespace server
{

server::player_id const
player_id_from_net(
	sanguis::net::id
);

}
}

#endif
