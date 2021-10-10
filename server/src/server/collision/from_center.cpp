#include <sanguis/collision/center.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/collision/from_center.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/math/vector/map.hpp>

sanguis::server::center
sanguis::server::collision::from_center(sanguis::collision::center const &_center)
{
  return sanguis::server::center{
      fcppt::math::vector::map(_center.get(), fcppt::boost_units_value{})};
}
