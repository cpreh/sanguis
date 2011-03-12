#ifndef SANGUIS_SERVER_ENTITIES_SPEED_TO_ABS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPEED_TO_ABS_HPP_INCLUDED

#include "property/value.hpp"
#include "../space_unit.hpp"
#include "../pos_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

pos_type const
speed_to_abs(
	space_unit direction_,
	property::value
);

}
}
}

#endif
