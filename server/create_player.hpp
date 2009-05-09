#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include "send_callback.hpp"
#include "environment_fwd.hpp"
#include "entities/container.hpp"
#include "entities/player_fwd.hpp"
#include "../connect_state.hpp"
#include "../messages/client_info.hpp"
#include "../net/id_type.hpp"

namespace sanguis
{
namespace server
{

entities::player * 
create_player(
	messages::client_info const &,
	send_callback const &send_to_player,
	environment const &,
	entities::container const &entities,
	connect_state::type const current_state,
	net::id_type);

}
}

#endif
