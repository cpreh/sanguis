#ifndef SANGUIS_COLLISION_IMPL_MOVE_CIRCLE_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_MOVE_CIRCLE_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/impl/circle.hpp>
#include <sanguis/collision/impl/move.hpp>


namespace sanguis::collision::impl
{

inline
sanguis::collision::impl::circle
move_circle(
	sanguis::collision::impl::circle const &_circle,
	sanguis::collision::speed const &_speed,
	sanguis::collision::duration const _duration
)
{
	return
		sanguis::collision::impl::circle{
			sanguis::collision::impl::move(
				sanguis::collision::center{
					_circle.origin()
				},
				_speed,
				_duration
			).get(),
			_circle.radius()
		};
}

}

#endif
