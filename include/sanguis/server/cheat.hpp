#ifndef SANGUIS_SERVER_CHEAT_HPP_INCLUDED
#define SANGUIS_SERVER_CHEAT_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/entities/player_fwd.hpp>


namespace sanguis
{
namespace server
{

void
cheat(
	sanguis::diff_clock const &,
	sanguis::server::entities::player &,
	sanguis::cheat_type
);

}
}

#endif
