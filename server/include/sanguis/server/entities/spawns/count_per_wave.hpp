#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_COUNT_PER_WAVE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_COUNT_PER_WAVE_HPP_INCLUDED

#include <sanguis/server/entities/spawns/size_type.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::entities::spawns
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::entities::spawns::size_type,
	count_per_wave
);

}

#endif
