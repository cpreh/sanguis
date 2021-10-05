#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_INTERVAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_INTERVAL_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/declare_strong_typedef.hpp>


namespace sanguis::server::entities::spawns
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sanguis::duration,
	interval
);

}

#endif
