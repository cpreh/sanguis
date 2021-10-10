#include <sanguis/collision/test.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/to_center.hpp>
#include <sanguis/server/collision/to_radius.hpp>
#include <sanguis/server/collision/with_world.hpp>

bool sanguis::server::collision::with_world(
    sanguis::server::center const &_center,
    sanguis::server::radius const _radius,
    sanguis::creator::grid const &_grid)
{
  return sanguis::collision::test(
      sanguis::server::collision::to_center(_center),
      sanguis::server::collision::to_radius(_radius),
      _grid);
}
