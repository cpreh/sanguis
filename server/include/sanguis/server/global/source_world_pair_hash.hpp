#ifndef SANGUIS_SERVER_GLOBAL_SOURCE_WORLD_PAIR_HASH_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_SOURCE_WORLD_PAIR_HASH_HPP_INCLUDED

#include <sanguis/server/global/source_world_pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::global
{

struct source_world_pair_hash
{
  std::size_t operator()(sanguis::server::global::source_world_pair const &) const noexcept;
};
}

#endif
