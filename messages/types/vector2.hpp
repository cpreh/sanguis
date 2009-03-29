#ifndef SANGUIS_MESSAGES_TYPES_VECTOR2_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_VECTOR2_HPP_INCLUDED

#include "space_unit.hpp"
#include <sge/math/vector/static.hpp>

namespace sanguis
{
namespace messages
{
namespace types
{

typedef sge::math::vector::static_<
	space_unit,
	2u
>::type vector2;

}
}
}

#endif
