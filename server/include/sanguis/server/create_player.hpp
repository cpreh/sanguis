#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include <sanguis/player_name_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/console_command_vector.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/entities/player_unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>


namespace sanguis
{
namespace server
{

sanguis::server::entities::player_unique_ptr
create_player(
	sanguis::random_generator &,
	sanguis::server::environment::load_context &,
	sanguis::player_name const &,
	sanguis::server::unicast_callback const &,
	sanguis::server::player_id,
	sanguis::server::console_command_vector const &
);

}
}

#endif
