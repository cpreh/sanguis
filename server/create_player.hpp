#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include "environment/object_fwd.hpp"
#include "entities/container.hpp"
#include "entities/player_auto_ptr.hpp"
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
	environment::object_ptr,
	connect_state::type const current_state,
	net::id_type
);

}
}

#endif
