#ifndef SANGUIS_COLLISION_VELOCITY_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_VELOCITY_FWD_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/units_fwd.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{

using
velocity
=
boost::units::quantity<
	boost::units::si::velocity,
	sanguis::collision::unit
>;

}
}

#endif
