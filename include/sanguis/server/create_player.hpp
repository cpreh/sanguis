#ifndef SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_CREATE_PLAYER_HPP_INCLUDED

#include <sanguis/server/entities/player_unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/console_command_vector.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>


namespace sanguis
{
namespace server
{

entities::player_unique_ptr
create_player(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	environment::load_context &,
	sge::charconv::system &,
	server::string const &name,
	server::unicast_callback const &send_to_player,
	server::player_id,
	server::console_command_vector const &
);

}
}

#endif
