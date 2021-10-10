#ifndef SANGUIS_COLLISION_WORLD_BODY_ENTER_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_ENTER_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_enter_fwd.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_base_ref.hpp>

namespace sanguis::collision::world
{

class body_enter
{
public:
  body_enter(
      sanguis::collision::world::body_base_ref,
      sanguis::collision::world::ghost_base_ref,
      sanguis::collision::world::created);

  [[nodiscard]] SANGUIS_COLLISION_SYMBOL sanguis::collision::world::body_base &body() const;

  [[nodiscard]] SANGUIS_COLLISION_SYMBOL sanguis::collision::world::ghost_base &ghost() const;

  [[nodiscard]] SANGUIS_COLLISION_SYMBOL sanguis::collision::world::created created() const;

private:
  sanguis::collision::world::body_base_ref body_;

  sanguis::collision::world::ghost_base_ref ghost_;

  sanguis::collision::world::created created_;
};

}

#endif
