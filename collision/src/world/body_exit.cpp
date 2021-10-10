#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_exit.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_base_ref.hpp>

sanguis::collision::world::body_exit::body_exit(
    sanguis::collision::world::body_base_ref const _body,
    sanguis::collision::world::ghost_base_ref const _ghost)
    : body_(_body), ghost_(_ghost)
{
}

sanguis::collision::world::body_base &sanguis::collision::world::body_exit::body() const
{
  return body_.get();
}

sanguis::collision::world::ghost_base &sanguis::collision::world::body_exit::ghost() const
{
  return ghost_.get();
}
