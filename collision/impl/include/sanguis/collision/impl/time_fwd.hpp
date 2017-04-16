#ifndef SANGUIS_COLLISION_IMPL_TIME_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_TIME_FWD_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/units_fwd.hpp>
#include <boost/units/systems/si/time.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

typedef
boost::units::quantity<
	boost::units::si::time,
	sanguis::collision::unit
>
time;

}
}
}

#endif
