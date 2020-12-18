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
	sanguis::collision::impl::line_segment const &movement,
	sanguis::collision::radius const &entity_radius,
	sanguis::collision::impl::rect const &obstacle,
	sanguis::collision::speed const &old_speed
);

}
}
}

#endif
