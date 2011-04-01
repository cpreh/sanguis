#ifndef SANGUIS_SERVER_ENTITIES_SPEED_TO_ABS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPEED_TO_ABS_HPP_INCLUDED

#include "property/value.hpp"
#include "../direction.hpp"
#include "../speed.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

server::speed const
speed_to_abs(
	server::direction,
	property::value
);

}
}
}

#endif
