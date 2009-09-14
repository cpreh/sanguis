#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include "entities/player_auto_ptr.hpp"
#include "environment/object_ptr.hpp"
#include "string.hpp"
#include "unicast_callback.hpp"
#include "player_id.hpp"
#include "../connect_state.hpp"

namespace sanguis
{
namespace server
{

entities::player_auto_ptr
create_player(
	environment::object_ptr,
	string const &name,
	unicast_callback const &send_to_player,
	connect_state::type current_state,
	player_id
);

}
}

#endif
