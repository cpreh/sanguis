#include <sanguis/collision/radius.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/to_radius.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/length.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::collision::radius
sanguis::server::collision::to_radius(sanguis::server::radius const _radius)
{
  return sanguis::collision::radius{_radius.get() * boost::units::si::meter};
}
