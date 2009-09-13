#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include "entities/player_auto_ptr.hpp"
#include "string.hpp"
#include "unicast_callback.hpp"
#include "../connect_state.hpp"
#include "../net/id_type.hpp"

namespace sanguis
{
namespace server
{

entities::player_auto_ptr
create_player(
	string const &name,
	unicast_callback const &send_to_player,
	connect_state::type current_state,
	net::id_type
);

}
}

#endif
