#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_collision.hpp>

sanguis::collision::world::body_collision::body_collision(
    sanguis::collision::world::body_base_ref const _body1,
    sanguis::collision::world::body_base_ref const _body2)
    : body1_(_body1), body2_(_body2)
{
}

sanguis::collision::world::body_base &sanguis::collision::world::body_collision::body1() const
{
  return body1_.get();
}

sanguis::collision::world::body_base &sanguis::collision::world::body_collision::body2() const
{
  return body2_.get();
}
