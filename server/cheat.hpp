#ifndef SANGUIS_SERVER_CHEAT_HPP_INCLUDED
#define SANGUIS_SERVER_CHEAT_HPP_INCLUDED

#include "entities/player_fwd.hpp"
#include "../cheat_type.hpp"

namespace sanguis
{
namespace server
{

void
cheat(
	entities::player &,
	cheat_type::type
);

}
}

#endif
