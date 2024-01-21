#ifndef SANGUIS_TILES_COLLECTION_HPP_INCLUDED
#define SANGUIS_TILES_COLLECTION_HPP_INCLUDED

#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/tiles/collection_fwd.hpp> // IWYU pragma: keep
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/pair_comparison.hpp> // IWYU pragma: keep
#include <sanguis/tiles/pair_std_hash.hpp> // IWYU pragma: keep
#include <sanguis/tiles/set.hpp>
#include <sanguis/tiles/symbol.hpp>
#include <sge/image2d/system_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tiles
{

class collection
{
  FCPPT_NONMOVABLE(collection);

public:
  SANGUIS_TILES_SYMBOL
  explicit collection(sge::image2d::system_ref);

  SANGUIS_TILES_SYMBOL
  ~collection();

  template <typename Tile>
  [[nodiscard]] sanguis::creator::enable_if_tile<Tile, sanguis::tiles::set<Tile> const &>
      set(sanguis::tiles::pair<Tile>);

private:
  template <typename Tile>
  using tile_map = std::unordered_map<sanguis::tiles::pair<Tile>, sanguis::tiles::set<Tile>>;

  sge::image2d::system_ref const image_system_;

  boost::fusion::set<tile_map<sanguis::creator::tile>, tile_map<sanguis::creator::background_tile>>
      tiles_;
};

}

#define SANGUIS_TILES_DECLARE_COLLECTION_SET(tile_type) \
  extern template sanguis::creator:: \
      enable_if_tile<tile_type, sanguis::tiles::set<tile_type> const &> \
      sanguis::tiles::collection::set(sanguis::tiles::pair<tile_type>)

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_DECLARE_COLLECTION_SET);

#endif
