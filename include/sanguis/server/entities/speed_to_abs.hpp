#ifndef SANGUIS_SERVER_ENTITIES_SPEED_TO_ABS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPEED_TO_ABS_HPP_INCLUDED

#include <sanguis/server/entities/property/value.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/speed.hpp>

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
