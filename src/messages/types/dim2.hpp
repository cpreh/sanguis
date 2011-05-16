#ifndef SANGUIS_MESSAGES_TYPES_DIM2_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_DIM2_HPP_INCLUDED

#include "size.hpp"
#include <fcppt/math/dim/static.hpp>

namespace sanguis
{
namespace messages
{
namespace types
{

typedef fcppt::math::dim::static_<
	types::size,
	2u
>::type dim2;

}
}
}

#endif
