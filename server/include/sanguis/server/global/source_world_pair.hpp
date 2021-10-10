#ifndef SANGUIS_SERVER_GLOBAL_SOURCE_WORLD_PAIR_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_SOURCE_WORLD_PAIR_HPP_INCLUDED

#include <sanguis/creator/opening.hpp>
#include <sanguis/server/source_world_id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::global
{

using source_world_pair = std::pair<sanguis::server::source_world_id, sanguis::creator::opening>;

}

#endif
