#ifndef SANGUIS_SERVER_PLAYER_ID_FROM_NET_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_ID_FROM_NET_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <alda/net/id.hpp>


namespace sanguis
{
namespace server
{

sanguis::server::player_id const
player_id_from_net(
	alda::net::id
);

}
}

#endif