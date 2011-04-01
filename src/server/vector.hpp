#ifndef SANGUIS_SERVER_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_VECTOR_HPP_INCLUDED

#include "space_unit.hpp"
#include <fcppt/math/vector/static.hpp>

namespace sanguis
{
namespace server
{

typedef fcppt::math::vector::static_<
	space_unit,
	2
>::type vector;

}
}

#endif
