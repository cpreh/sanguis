#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_ENTRY_SET_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_ENTRY_SET_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/strong_typedef_std_hash.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::world
{

using sight_range_entry_set = std::unordered_set<sanguis::entity_id>;

}

#endif
