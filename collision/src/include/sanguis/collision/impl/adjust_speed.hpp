#ifndef SANGUIS_COLLISION_IMPL_ADJUST_SPEED_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_ADJUST_SPEED_HPP_INCLUDED

#include <sanguis/collision/dim2_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/impl/line_segment_fwd.hpp>
#include <sanguis/collision/impl/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

sanguis::collision::speed const
adjust_speed(
	sanguis::collision::impl::line_segment movement,
	sanguis::collision::dim2 entity_size,
	sanguis::collision::impl::rect obstacle,
	sanguis::collision::speed old_speed
);

}
}
}

#endif
