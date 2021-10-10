#ifndef SANGUIS_SERVER_MASS_UNIT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_MASS_UNIT_FWD_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/units_fwd.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server
{

using mass_unit = boost::units::quantity<boost::units::si::mass, sanguis::server::space_unit>;

}

#endif
