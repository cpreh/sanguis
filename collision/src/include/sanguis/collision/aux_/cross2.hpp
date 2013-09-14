#ifndef SANGUIS_COLLISION_AUX__CROSS2_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__CROSS2_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{

inline
sanguis::collision::unit
cross2(
	sanguis::collision::vector2 const _a,
	sanguis::collision::vector2 const _b
)
{
	return
		_a.x() * _b.y()
		-
		_a.y() * _b.x();
}

}
}
}

#endif
