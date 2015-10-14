#ifndef SANGUIS_COLLISION_IMPL_ADJUST_SPEED_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_ADJUST_SPEED_HPP_INCLUDED

#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/impl/line_segment_fwd.hpp>
#include <sanguis/collision/impl/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

sanguis::collision::speed
adjust_speed(
	sanguis::collision::impl::line_segment movement,
	sanguis::collision::radius entity_radius,
	sanguis::collision::impl::rect obstacle,
	sanguis::collision::speed old_speed
);

}
}
}

#endif
