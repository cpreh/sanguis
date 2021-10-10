#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/collision/distance_pos_pos.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>

sanguis::server::space_unit sanguis::server::collision::distance_pos_pos(
    sanguis::server::vector const &_a, sanguis::server::vector const &_b)
{
  return fcppt::math::vector::length(_a - _b);
}
