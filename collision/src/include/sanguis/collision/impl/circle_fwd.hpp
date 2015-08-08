#ifndef SANGUIS_COLLISION_IMPL_CIRCLE_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_CIRCLE_FWD_HPP_INCLUDED

#include <sanguis/collision/length_fwd.hpp>
#include <fcppt/math/sphere/circle_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

typedef
fcppt::math::sphere::circle<
	sanguis::collision::length
>
circle;

}
}
}

#endif
