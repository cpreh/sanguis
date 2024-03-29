#include <sanguis/collision/log_cref.hpp>
#include <sanguis/collision/log_fwd.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/collision/world/object_ref.hpp>
#include <sanguis/creator/grid_cref.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>

sanguis::server::entities::transfer_parameters::transfer_parameters(
    sanguis::collision::log_cref const _log,
    sanguis::collision::world::object_ref const _world,
    sanguis::collision::world::created const _created,
    sanguis::creator::grid_cref const _grid,
    sanguis::server::center const _center,
    sanguis::server::angle const _angle)
    : log_{_log}, world_(_world), created_{_created}, grid_(_grid), center_(_center), angle_(_angle)
{
}

sanguis::collision::log const &sanguis::server::entities::transfer_parameters::log() const
{
  return log_.get();
}

sanguis::collision::world::object &sanguis::server::entities::transfer_parameters::world() const
{
  return world_.get();
}

sanguis::collision::world::created sanguis::server::entities::transfer_parameters::created() const
{
  return created_;
}

sanguis::creator::grid const &sanguis::server::entities::transfer_parameters::grid() const
{
  return grid_.get();
}

sanguis::server::center sanguis::server::entities::transfer_parameters::center() const
{
  return center_;
}

sanguis::server::angle sanguis::server::entities::transfer_parameters::angle() const
{
  return angle_;
}
