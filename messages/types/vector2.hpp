#ifndef SANGUIS_MESSAGES_TYPES_VECTOR2_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_VECTOR2_HPP_INCLUDED

#include "space_unit.hpp"
#include <fcppt/math/vector/static.hpp>

namespace sanguis
{
namespace messages
{
namespace types
{

typedef fcppt::math::vector::static_<
	space_unit,
	2u
>::type vector2;

}
}
}

#endif
