#ifndef SANGUIS_SERVER_POS_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_POS_TYPE_HPP_INCLUDED

#include "space_unit.hpp"
#include <sge/math/vector/static.hpp>

namespace sanguis
{
namespace server
{

typedef sge::math::vector::static_<
	space_unit,
	2
>::type pos_type;

}
}

#endif
