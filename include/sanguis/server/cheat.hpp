#ifndef SANGUIS_SERVER_CHEAT_HPP_INCLUDED
#define SANGUIS_SERVER_CHEAT_HPP_INCLUDED

#include <sanguis/server/entities/player_fwd.hpp>
#include <sanguis/cheat_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>

namespace sanguis
{
namespace server
{

void
cheat(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	entities::player &,
	cheat_type::type
);

}
}

#endif
