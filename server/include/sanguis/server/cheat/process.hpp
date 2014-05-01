#ifndef SANGUIS_SERVER_CHEAT_PROCESS_HPP_INCLUDED
#define SANGUIS_SERVER_CHEAT_PROCESS_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/entities/player_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace cheat
{

void
process(
	sanguis::random_generator &,
	sanguis::server::entities::player &,
	sanguis::cheat_type,
	sanguis::server::unicast_callback const &
);

}
}
}

#endif
