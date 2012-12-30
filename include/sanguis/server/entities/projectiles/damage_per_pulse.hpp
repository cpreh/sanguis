#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_DAMAGE_PER_PULSE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_DAMAGE_PER_PULSE_HPP_INCLUDED

#include <sanguis/server/damage/unit.hpp>
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
	sanguis::server::damage::unit,
	damage_per_pulse
);

}
}
}
}

#endif
