#ifndef SANGUIS_SERVER_SEND_AVAILABLE_PERKS_HPP_INCLUDED
#define SANGUIS_SERVER_SEND_AVAILABLE_PERKS_HPP_INCLUDED

#include "send_callback.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
class player;
}

void send_available_perks(
	entities::player &,
	send_callback const &);

}
}

#endif
