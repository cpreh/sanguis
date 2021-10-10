#include <sanguis/collision/radius.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/from_radius.hpp>

sanguis::server::radius
sanguis::server::collision::from_radius(sanguis::collision::radius const &_radius)
{
  return sanguis::server::radius{_radius.get().value()};
}
