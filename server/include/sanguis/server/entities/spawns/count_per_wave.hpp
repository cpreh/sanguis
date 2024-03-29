#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_COUNT_PER_WAVE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_COUNT_PER_WAVE_HPP_INCLUDED

#include <sanguis/server/entities/spawns/size_type.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::entities::spawns
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::server::entities::spawns::size_type, count_per_wave);

}

#endif
