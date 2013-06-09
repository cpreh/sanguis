#ifndef SANGUIS_COLLISION_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/optional_vector2_fwd.hpp>
#include <sanguis/collision/rect_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/vector2_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::optional_vector2 const
intersection(
	sanguis::collision::rect,
	sanguis::collision::vector2,
	sanguis::collision::speed
);

}
}

#endif
