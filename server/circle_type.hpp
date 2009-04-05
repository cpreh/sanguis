#ifndef SANGUIS_SERVER_CIRCLE_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_CIRCLE_TYPE_HPP_INCLUDED

#include "space_unit.hpp"
#include <sge/math/circle_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef sge::math::circle<
	space_unit
> circle_type;

}
}

#endif
