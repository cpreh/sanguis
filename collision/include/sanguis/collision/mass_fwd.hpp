#ifndef SANGUIS_COLLISION_MASS_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_MASS_FWD_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/units_fwd.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::collision
{

using mass = boost::units::quantity<boost::units::si::mass, sanguis::collision::unit>;

}

#endif
