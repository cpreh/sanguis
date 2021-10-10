#ifndef SANGUIS_TILES_IMPL_DRAW_NON_CONNECTING_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_DRAW_NON_CONNECTING_HPP_INCLUDED

#include <sanguis/creator/min.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/sup.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection_ref.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/pos.hpp>
#include <sanguis/tiles/impl/draw_base.hpp>
#include <sanguis/tiles/impl/get_content_function.hpp>
#include <sanguis/tiles/impl/non_connecting_images.hpp>
#include <sanguis/tiles/impl/shift.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/vector/null.hpp>

namespace sanguis::tiles::impl
{

template <typename Tile>
sanguis::tiles::cell_container draw_non_connecting(
    fcppt::log::object &_log, // NOLINT(google-runtime-references)
    sanguis::tiles::collection_ref const _collection,
    sanguis::tiles::error const _error_code,
    sanguis::creator::tile_grid<Tile> const &_grid,
    sanguis::creator::min const _min,
    sanguis::creator::sup const _sup)
{
  return sanguis::tiles::impl::draw_base(
      _grid,
      _min,
      _sup,
      sanguis::tiles::impl::shift{fcppt::math::vector::null<sanguis::tiles::pos>()},
      sanguis::tiles::impl::get_content_function{
          [&_log, _collection, &_grid, _error_code](sanguis::creator::pos const _pos) {
            return sanguis::tiles::impl::non_connecting_images(
                _log, _collection, _error_code, _grid, _pos);
          }});
}

}

#endif
