#ifndef SANGUIS_COLLISION_IMPL_CROSS2_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_CROSS2_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sanguis::collision::impl
{

inline sanguis::collision::unit cross2(
    fcppt::math::vector::static_<sanguis::collision::unit, 2> const &_a,
    fcppt::math::vector::static_<sanguis::collision::unit, 2> const &_b)
{
  return _a.x() * _b.y() - _a.y() * _b.x();
}

}

#endif
