#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/player_unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/console_command_vector.hpp>


namespace sanguis
{
namespace server
{

sanguis::server::entities::player_unique_ptr
create_player(
	sanguis::random_generator &,
	sanguis::server::environment::load_context &,
	sanguis::server::string const &name,
	sanguis::server::unicast_callback const &send_to_player,
	sanguis::server::player_id,
	sanguis::server::console_command_vector const &
);

}
}

#endif
