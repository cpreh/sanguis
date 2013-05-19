#ifndef SANGUIS_SERVER_SEND_AVAILABLE_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_AVAILABLE_PERKS_HPP_INCLUDED

#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/entities/player_fwd.hpp>


namespace sanguis
{
namespace server
{

void
send_available_perks(
	sanguis::server::entities::player const &,
	sanguis::server::unicast_callback const &
);

}
}

#endif
