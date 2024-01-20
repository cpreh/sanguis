#ifndef SANGUIS_COLLISION_WORLD_BODY_COLLISION_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_COLLISION_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_collision_fwd.hpp> // IWYU pragma: keep

namespace sanguis::collision::world
{

class body_collision
{
public:
  body_collision(
      sanguis::collision::world::body_base_ref, sanguis::collision::world::body_base_ref);

  [[nodiscard]] SANGUIS_COLLISION_SYMBOL sanguis::collision::world::body_base &body1() const;

  [[nodiscard]] SANGUIS_COLLISION_SYMBOL sanguis::collision::world::body_base &body2() const;

private:
  sanguis::collision::world::body_base_ref body1_;

  sanguis::collision::world::body_base_ref body2_;
};

}

#endif
