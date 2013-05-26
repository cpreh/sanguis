#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_PULSE_TIME_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_PULSE_TIME_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace projectiles
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	pulse_time
);

}
}
}
}

#endif
