#ifndef SANGUIS_SERVER_ENTITIES_SPEED_TO_ABS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPEED_TO_ABS_HPP_INCLUDED

#include <sanguis/server/direction.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

sanguis::server::speed const
speed_to_abs(
	sanguis::server::direction,
	sanguis::server::entities::property::value
);

}
}
}

#endif
