#ifndef SANGUIS_MESSAGES_TYPES_DIM_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_DIM_HPP_INCLUDED

#include "space_unit.hpp"
#include <sge/math/dim/static.hpp>

namespace sanguis
{
namespace messages
{
namespace types
{

typedef sge::math::dim::static_<
	space_unit,
	2u
>::type dim;

}
}
}

#endif
