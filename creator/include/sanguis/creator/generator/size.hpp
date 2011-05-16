#ifndef SANGUIS_CREATOR_GENERATOR_SIZE_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_SIZE_HPP_INCLUDED

#include <sanguis/creator/geometry/unit.hpp>
#include <fcppt/math/dim/static.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{

typedef fcppt::math::dim::static_<
	geometry::unit,
	2
>::type size;

}
}
}

#endif
