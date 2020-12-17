#ifndef SANGUIS_COLLISION_LENGTH_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_LENGTH_FWD_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/units_fwd.hpp>
#include <boost/units/systems/si/length.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{

using
length
=
boost::units::quantity<
	boost::units::si::length,
	sanguis::collision::unit
>;

}
}

#endif
