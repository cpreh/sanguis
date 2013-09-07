#ifndef SANGUIS_COLLISION_DIM2_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_DIM2_FWD_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sanguis
{
namespace collision
{

typedef
fcppt::math::dim::static_<
	sanguis::collision::unit,
	2
> dim2;

}
}

#endif
