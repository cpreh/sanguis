#ifndef SANGUIS_CREATOR_IMPL_MAZE_TO_TILE_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_MAZE_TO_TILE_GRID_HPP_INCLUDED

#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/make_pos_ref_crange.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/dim.hpp> // IWYU pragma: keep
#include <fcppt/math/vector/output.hpp> // IWYU pragma: keep
#include <fcppt/optional/to_exception.hpp>

namespace sanguis::creator::impl
{

template <typename Tile>
sanguis::creator::tile_grid<Tile> maze_to_tile_grid(
    sanguis::creator::impl::reachable_grid const &_maze,
    unsigned const _wall_thickness,
    unsigned const _spacing,
    Tile const _empty,
    Tile const _wall)
{
  using grid_type = sanguis::creator::tile_grid<Tile>;

  using dim_type = sanguis::creator::impl::reachable_grid::dim;

  // the (always empty) "core" cells in the maze (3x3)
  // form a pattern of walls (w) and spaces like on the left,
  // then get connected by more empty cells to form the maze.
  //
  // With the added 1-wall border, an nxn grid becomes a (2n+1)x(2n+1) grid.
  //
  //  3x3                           7x7
  //
  //                              bbbbbbb
  // o o o    _w_w_      _w___    b_w___b
  //          wwwww      _www_    b_www_b
  // o o o => _w_w_  =>  _____ => b_____b
  //          wwwww      ww_w_    bww_w_b
  // o o o    _w_w_      ___w_    b___w_b
  //                              bbbbbbb

  // get the "original maze size"
  dim_type const real_size(
      ((_maze.size() - fcppt::math::dim::fill<dim_type>(1U)) / 2U).get_unsafe());

  // empty spaces are scaled with _spacing
  // walls and connections are scaled with _wall_thickness,
  // there are n open spaces separated by (n-1) walls in each dimension
  // (so there are 4 types of rectangles in the final grid)
  dim_type const result_size(
      real_size * _spacing + (real_size - fcppt::math::dim::fill<dim_type>(1U)) * _wall_thickness +
      // leave a gap around the edge
      fcppt::math::dim::fill<dim_type>(2U));

  auto const coordinate_transform(
      [_wall_thickness, _spacing](dim_type::value_type const _a)
      { return ((_a / 2) * _spacing) + (((_a + 1) / 2) * _wall_thickness); });

  auto const wall_or_space([_wall_thickness, _spacing](dim_type::value_type const _a)
                           { return _a % 2 == 0 ? _wall_thickness : _spacing; });

  grid_type result{result_size, sanguis::creator::tile::nothing};

  for (auto cell : fcppt::container::grid::make_pos_ref_crange(_maze))
  {
    typename grid_type::pos const start(
        // leave one space for the edge
        coordinate_transform(cell.pos().x()),
        coordinate_transform(cell.pos().y()));

    dim_type const cell_size(wall_or_space(cell.pos().x()), wall_or_space(cell.pos().y()));

    for (dim_type::value_type y = 0U; y < cell_size.h(); ++y)
    {
      for (dim_type::value_type x = 0U; x < cell_size.w(); ++x)
      {
        typename grid_type::pos const pos{start + dim_type(x, y)};

        fcppt::optional::to_exception(
            fcppt::container::grid::at_optional(result, pos),
            [pos]
            {
              return sanguis::creator::exception{
                  FCPPT_TEXT("Position ") + fcppt::output_to_fcppt_string(pos) +
                  FCPPT_TEXT(" out of range!")};
            })
            .get() = cell.value() == sanguis::creator::impl::reachable(true) ? _empty : _wall;
      }
    }
  }

  return result;
}

}

#endif
