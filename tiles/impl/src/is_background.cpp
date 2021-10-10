#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/enable_if_tile.hpp>
#include <sanguis/creator/instantiate_tile.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/tiles/is_background.hpp>
#include <sanguis/tiles/impl/is_background.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Tile>
struct is_background_impl;

template <>
struct is_background_impl<sanguis::creator::tile> : std::false_type
{
};

template <>
struct is_background_impl<sanguis::creator::background_tile> : std::true_type
{
};

FCPPT_PP_POP_WARNING

}

template <typename Tile>
sanguis::creator::enable_if_tile<Tile, sanguis::tiles::is_background>
sanguis::tiles::impl::is_background()
{
  return sanguis::tiles::is_background{is_background_impl<Tile>::value};
}

#define SANGUIS_TILES_INSTANTIATE_IS_BACKGROUND(tile_type) \
  template sanguis::creator::enable_if_tile<tile_type, sanguis::tiles::is_background> \
  sanguis::tiles::impl::is_background<tile_type>()

SANGUIS_CREATOR_INSTANTIATE_TILE(SANGUIS_TILES_INSTANTIATE_IS_BACKGROUND);
