#ifndef SANGUIS_SERVER_ENTITIES_MOVEMENT_SPEED_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_MOVEMENT_SPEED_FWD_HPP_INCLUDED

#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::entities::property::value,
	movement_speed
);

}
}
}

#endif
