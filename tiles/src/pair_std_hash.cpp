#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/pair_std_hash.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/hash_combine.hpp>
#include <fcppt/cast/enum_to_underlying.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

template <typename Tile>
std::size_t
std::hash<sanguis::tiles::pair<Tile>>::operator()(sanguis::tiles::pair<Tile> const _pair) const
{
  std::hash<std::underlying_type_t<Tile>> const hash_element{};

  return fcppt::hash_combine(
      hash_element(fcppt::cast::enum_to_underlying(_pair.first())),
      hash_element(fcppt::cast::enum_to_underlying(_pair.second())));
}

#define SANGUIS_TILES_INSTANTIATE_TILE_STD_HASH(tile_type) \
  template struct std::hash<sanguis::tiles::pair<tile_type>\
>

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_INSTANTIATE_TILE_STD_HASH);
