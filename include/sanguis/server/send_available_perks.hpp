#ifndef SANGUIS_SERVER_SEND_AVAILABLE_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_AVAILABLE_PERKS_HPP_INCLUDED

#include <sanguis/server/entities/player_fwd.hpp>
#include <sanguis/server/unicast_callback.hpp>

namespace sanguis
{
namespace server
{

void
send_available_perks(
	entities::player const &,
	server::unicast_callback const &
);

}
}

#endif
