#ifndef SANGUIS_COLLISION_IMPL_MOVE_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_MOVE_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/impl/duration_to_time.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


namespace sanguis::collision::impl
{

inline
sanguis::collision::center
move(
	sanguis::collision::center const &_center,
	sanguis::collision::speed const &_speed,
	sanguis::collision::duration const _duration
)
{
	return
		sanguis::collision::center{
			_center.get()
			+
			_speed
			*
			sanguis::collision::impl::duration_to_time(
				_duration
			)
		};
}

}

#endif
