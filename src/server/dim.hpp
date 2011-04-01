#ifndef SANGUIS_SERVER_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_DIM_HPP_INCLUDED

#include "space_unit.hpp"
#include <fcppt/math/dim/static.hpp>

namespace sanguis
{
namespace server
{

typedef fcppt::math::dim::static_<
	server::space_unit,
	2
>::type dim;

}
}

#endif
