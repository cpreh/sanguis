#ifndef SANGUIS_SERVER_CIRCLE_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_CIRCLE_TYPE_HPP_INCLUDED

#include "space_unit.hpp"
#include <fcppt/math/circle/basic_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef fcppt::math::circle::basic<
	space_unit
> circle_type;

}
}

#endif
