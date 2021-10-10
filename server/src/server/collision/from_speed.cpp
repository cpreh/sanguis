#include <sanguis/collision/speed.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/from_speed.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/math/vector/map.hpp>

sanguis::server::speed
sanguis::server::collision::from_speed(sanguis::collision::speed const &_speed)
{
  return sanguis::server::speed{fcppt::math::vector::map(_speed, fcppt::boost_units_value{})};
}
