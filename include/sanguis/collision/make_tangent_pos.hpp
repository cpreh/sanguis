#ifndef SANGUIS_COLLISION_MAKE_TANGENT_POS_HPP_INCLUDED
#define SANGUIS_COLLISION_MAKE_TANGENT_POS_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/pos_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/vector2_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::pos const
make_tangent_pos(
	sanguis::collision::center,
	sanguis::collision::radius,
	sanguis::collision::vector2 perp
);

}
}

#endif
