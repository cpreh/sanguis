#include <sanguis/collision/center.hpp>
#include <sanguis/collision/impl/world/simple/grid_position.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_unsigned.hpp>

sanguis::creator::pos
sanguis::collision::impl::world::simple::grid_position(sanguis::collision::center const &_center)
{
  return (fcppt::math::vector::to_unsigned(
              fcppt::math::vector::
                  structure_cast<sanguis::creator::signed_pos, fcppt::cast::float_to_int_fun>(
                      fcppt::math::vector::map(_center.get(), fcppt::boost_units_value{}))) /
          sanguis::creator::tile_size::value)
      .get_unsafe();
}
