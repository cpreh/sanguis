#include <sanguis/server/global/source_world_pair.hpp>
#include <sanguis/server/global/source_world_pair_hash.hpp>
#include <fcppt/hash.hpp>
#include <fcppt/hash_combine.hpp>
#include <fcppt/strong_typedef_std_hash.hpp> // IWYU pragma: keep
#include <fcppt/math/vector/std_hash.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

std::size_t sanguis::server::global::source_world_pair_hash::operator()(
    sanguis::server::global::source_world_pair const &_pair) const noexcept
{
  return fcppt::hash_combine(fcppt::hash(_pair.first), fcppt::hash(_pair.second));
}
