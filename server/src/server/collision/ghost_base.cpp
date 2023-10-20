#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_base_ref.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_base.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_end.hpp>

sanguis::server::collision::ghost_base::ghost_base() : sanguis::collision::world::ghost_base() {}

sanguis::server::collision::ghost_base::~ghost_base() = default;

void sanguis::server::collision::ghost_base::body_enter(
    sanguis::collision::world::body_base_ref const _body,
    sanguis::collision::world::created const _created)
{
  if (this->can_collide_with(_body.get()))
  {
    this->on_body_enter(_body, _created);
  }
}

void sanguis::server::collision::ghost_base::body_exit(sanguis::collision::world::body_base &_body)
{
  if (this->can_collide_with(_body))
  {
    this->on_body_exit(_body);
  }
}
