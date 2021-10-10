#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/body_enter.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_base_ref.hpp>

sanguis::collision::world::body_enter::body_enter(
    sanguis::collision::world::body_base_ref const _body,
    sanguis::collision::world::ghost_base_ref const _ghost,
    sanguis::collision::world::created const _created)
    : body_(_body), ghost_(_ghost), created_{_created}
{
}

sanguis::collision::world::body_base &sanguis::collision::world::body_enter::body() const
{
  return body_.get();
}

sanguis::collision::world::ghost_base &sanguis::collision::world::body_enter::ghost() const
{
  return ghost_.get();
}

sanguis::collision::world::created sanguis::collision::world::body_enter::created() const
{
  return created_;
}
