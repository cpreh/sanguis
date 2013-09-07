#ifndef SANGUIS_COLLISION_VECTOR2_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_VECTOR2_FWD_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/math/vector/static.hpp>


namespace sanguis
{
namespace collision
{

typedef
fcppt::math::vector::static_<
	sanguis::collision::unit,
	2
> vector2;

}
}

#endif
