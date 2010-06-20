#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include "entities/player_auto_ptr.hpp"
#include "environment/load_context_ptr.hpp"
#include "string.hpp"
#include "unicast_callback.hpp"
#include "player_id.hpp"
#include "console_command_vector.hpp"

namespace sanguis
{
namespace server
{

entities::player_auto_ptr
create_player(
	environment::load_context_ptr,
	string const &name,
	unicast_callback const &send_to_player,
	player_id,
	server::console_command_vector const &
);

}
}

#endif
