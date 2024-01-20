#ifndef SANGUIS_COLLISION_WORLD_GHOST_PARAMETERS_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GHOST_PARAMETERS_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_base_ref.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp> // IWYU pragma: keep

namespace sanguis::collision::world
{

class ghost_parameters
{
public:
  SANGUIS_COLLISION_SYMBOL
  ghost_parameters(
      sanguis::collision::center,
      sanguis::collision::radius,
      sanguis::collision::world::ghost_group,
      sanguis::collision::world::ghost_base_ref);

  [[nodiscard]] sanguis::collision::center center() const;

  [[nodiscard]] sanguis::collision::radius radius() const;

  [[nodiscard]] sanguis::collision::world::ghost_group collision_group() const;

  [[nodiscard]] sanguis::collision::world::ghost_base &ghost_base() const;

private:
  sanguis::collision::center center_;

  sanguis::collision::radius radius_;

  sanguis::collision::world::ghost_group collision_group_;

  sanguis::collision::world::ghost_base_ref ghost_base_;
};

}

#endif
