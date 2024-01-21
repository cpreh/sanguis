#ifndef SANGUIS_TILES_SET_HPP_INCLUDED
#define SANGUIS_TILES_SET_HPP_INCLUDED

#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/creator/is_tile.hpp>
#include <sanguis/tiles/orientation_map.hpp>
#include <sanguis/tiles/pair_fwd.hpp>
#include <sanguis/tiles/set_fwd.hpp> // IWYU pragma: keep
#include <sanguis/tiles/symbol.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tiles
{

template <typename Tile>
class set
{
  FCPPT_NONCOPYABLE(set);

  static_assert(sanguis::creator::is_tile<Tile>::value, "Tile must be a tile type");

public:
  SANGUIS_TILES_SYMBOL
  set(sge::image2d::system &, // NOLINT(google-runtime-references)
      sanguis::tiles::pair<Tile>);

  SANGUIS_TILES_SYMBOL
  set(set &&) noexcept;

  SANGUIS_TILES_SYMBOL
  set &operator=(set &&) noexcept;

  SANGUIS_TILES_SYMBOL
  ~set();

  [[nodiscard]] SANGUIS_TILES_SYMBOL sanguis::tiles::orientation_map const &orientations() const;

  [[nodiscard]] SANGUIS_TILES_SYMBOL std::filesystem::path const &path() const;

private:
  set(sge::image2d::system &, // NOLINT(google-runtime-references)
      std::filesystem::path const &);

  std::filesystem::path path_;

  sanguis::tiles::orientation_map orientations_;
};

}

#define SANGUIS_TILES_DECLARE_SET(tile_type) extern template class sanguis::tiles::set<tile_type>

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_DECLARE_SET);

#endif
