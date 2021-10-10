#ifndef SANGUIS_CREATOR_CENTER_TO_GRID_POS_HPP_INCLUDED
#define SANGUIS_CREATOR_CENTER_TO_GRID_POS_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

namespace sanguis::creator
{

template <typename Unit>
inline sanguis::creator::pos center_to_grid_pos(fcppt::math::vector::static_<Unit, 2> const _center)
{
  return (fcppt::math::vector::structure_cast<sanguis::creator::pos, fcppt::cast::static_cast_fun>(
              _center) /
          sanguis::creator::tile_size::value)
      .get_unsafe();
}

}

#endif
