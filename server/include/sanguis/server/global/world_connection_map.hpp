#ifndef SANGUIS_SERVER_GLOBAL_WORLD_CONNECTION_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_WORLD_CONNECTION_MAP_HPP_INCLUDED

#include <sanguis/server/global/dest_world_pair.hpp>
#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/global/source_world_pair_hash.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/math/vector/comparison.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::global
{

using world_connection_map = std::unordered_map<
    sanguis::server::global::source_world_pair,
    sanguis::server::global::dest_world_pair,
    sanguis::server::global::source_world_pair_hash>;
}

#endif
