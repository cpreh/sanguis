#include <sanguis/collision/center.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/collision/to_center.hpp>
#include <fcppt/math/vector/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/length.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::collision::center
sanguis::server::collision::to_center(sanguis::server::center const &_center)
{
  return sanguis::collision::center(fcppt::math::vector::map(
      _center.get(),
      [](sanguis::server::space_unit const _value) { return _value * boost::units::si::meter; }));
}
