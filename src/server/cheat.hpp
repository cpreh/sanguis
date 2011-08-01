#ifndef SANGUIS_SERVER_CHEAT_HPP_INCLUDED
#define SANGUIS_SERVER_CHEAT_HPP_INCLUDED

#include "entities/player_fwd.hpp"
#include "../cheat_type.hpp"
#include "../diff_clock_fwd.hpp"

namespace sanguis
{
namespace server
{

void
cheat(
	sanguis::diff_clock const &,
	entities::player &,
	cheat_type::type
);

}
}

#endif
