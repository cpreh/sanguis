#ifndef SANGUIS_COLLISION_IMPL_DURATION_TO_TIME_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_DURATION_TO_TIME_HPP_INCLUDED

#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/impl/time.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/time.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

// TODO: Can we make a generic function for this?
inline
sanguis::collision::impl::time
duration_to_time(
	sanguis::collision::duration const _duration
)
{
	return
		_duration.count()
		*
		boost::units::si::second;
}

}
}
}

#endif
