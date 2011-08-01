#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include "entities/player_unique_ptr.hpp"
#include "environment/load_context_fwd.hpp"
#include "string.hpp"
#include "unicast_callback.hpp"
#include "player_id.hpp"
#include "console_command_vector.hpp"
#include "../diff_clock_fwd.hpp"

namespace sanguis
{
namespace server
{

entities::player_unique_ptr
create_player(
	sanguis::diff_clock const &,
	environment::load_context &,
	string const &name,
	unicast_callback const &send_to_player,
	player_id,
	server::console_command_vector const &
);

}
}

#endif
