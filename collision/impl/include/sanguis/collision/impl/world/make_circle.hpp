#ifndef SANGUIS_COLLISION_IMPL_WORLD_MAKE_CIRCLE_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_MAKE_CIRCLE_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/impl/circle.hpp>

namespace sanguis::collision::impl::world
{

template <typename Type>
inline sanguis::collision::impl::circle make_circle(Type const &_object)
{
  return sanguis::collision::impl::circle{_object.center().get(), _object.radius().get()};
}

}

#endif
