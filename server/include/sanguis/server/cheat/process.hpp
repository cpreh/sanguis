#ifndef SANGUIS_SERVER_CHEAT_PROCESS_HPP_INCLUDED
#define SANGUIS_SERVER_CHEAT_PROCESS_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/entities/player_fwd.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>


namespace sanguis::server::cheat
{

void
process(
	sanguis::server::entities::player &, // NOLINT(google-runtime-references)
	sanguis::cheat_type,
	sanguis::server::weapons::common_parameters const &,
	sanguis::server::unicast_callback const &
);

}

#endif
