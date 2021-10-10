#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/tiles/impl/category.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

namespace
{

template <typename Tile>
struct category_any;

template <>
struct category_any<sanguis::creator::tile>
{
  static fcppt::string get() { return FCPPT_TEXT("foreground"); }
};

template <>
struct category_any<sanguis::creator::background_tile>
{
  static fcppt::string get() { return FCPPT_TEXT("background"); }
};

}

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, fcppt::string> sanguis::tiles::impl::category()
{
  return category_any<Tile>::get();
}

#define SANGUIS_TILES_INSTANTIATE_CATEGORY(tile_type) \
  template sanguis::creator::enable_if_tile<tile_type, fcppt::string> \
  sanguis::tiles::impl::category<tile_type>()

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_INSTANTIATE_CATEGORY);
