#ifndef SANGUIS_CREATOR_GENERATOR_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_SIZE_FWD_HPP_INCLUDED

#include <sanguis/creator/geometry/size_type.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sanguis
{
namespace creator
{
namespace generator
{

typedef fcppt::math::dim::static_<
	sanguis::creator::geometry::size_type,
	2
>::type size;

}
}
}

#endif
