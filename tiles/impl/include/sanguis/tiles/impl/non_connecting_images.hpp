#ifndef SANGUIS_TILES_IMPL_NON_CONNECTING_IMAGES_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_NON_CONNECTING_IMAGES_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/tiles/collection_ref.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/pair.hpp>
#include <sanguis/tiles/impl/error_message_function.hpp>
#include <sanguis/tiles/impl/filter_non_connecting.hpp>
#include <sanguis/tiles/impl/images_base.hpp>
#include <sanguis/tiles/impl/optional_content_path.hpp>
#include <sanguis/tiles/impl/to_string.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sanguis::tiles::impl
{

template <typename Tile>
sanguis::tiles::impl::optional_content_path non_connecting_images(
    fcppt::log::object &_log, // NOLINT(google-runtime-references)
    sanguis::tiles::collection_ref const _collection,
    sanguis::tiles::error const _error_code,
    sanguis::creator::tile_grid<Tile> const &_grid,
    sanguis::creator::pos const _pos)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
  return fcppt::optional::bind(
      fcppt::container::grid::at_optional(_grid, _pos),
      [&_log, &_collection, _error_code](fcppt::reference<Tile const> const _tile)
      {
        return sanguis::tiles::impl::filter_non_connecting(_tile.get())
                   ? sanguis::tiles::impl::optional_content_path{}
                   : sanguis::tiles::impl::images_base(
                         _log,
                         _collection,
                         _error_code,
                         sanguis::tiles::pair<Tile>(_tile.get(), _tile.get()),
                         sanguis::tiles::orientation::null(),
                         sanguis::tiles::impl::error_message_function{
                             [_tile] { return sanguis::tiles::impl::to_string(_tile.get()); }});
      });
  FCPPT_PP_POP_WARNING
}

}

#endif
