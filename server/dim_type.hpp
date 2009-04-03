#ifndef SANGUIS_SERVER_DIM_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_DIM_TYPE_HPP_INCLUDED

#include "space_unit.hpp"
#include <sge/math/dim/static.hpp>

namespace sanguis
{
namespace server
{

typedef sge::math::dim::static_<
	space_unit,
	2
>::type dim_type;

}
}

#endif
