#include <sanguis/collision/world/body_collision_container.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/update_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::collision::world::update_result::update_result(
    sanguis::collision::world::body_enter_container &&_body_enter,
    sanguis::collision::world::body_exit_container &&_body_exit,
    sanguis::collision::world::body_collision_container &&_body_collision)
    : body_enter_(std::move(_body_enter)),
      body_exit_(std::move(_body_exit)),
      body_collision_(std::move(_body_collision))
{
}

sanguis::collision::world::body_enter_container const &
sanguis::collision::world::update_result::body_enter() const
{
  return body_enter_;
}

sanguis::collision::world::body_exit_container const &
sanguis::collision::world::update_result::body_exit() const
{
  return body_exit_;
}

sanguis::collision::world::body_collision_container const &
sanguis::collision::world::update_result::body_collision() const
{
  return body_collision_;
}
