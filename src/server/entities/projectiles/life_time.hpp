#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_LIFE_TIME_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_LIFE_TIME_HPP_INCLUDED

#include "../../../time_delta.hpp"
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
	sanguis::time_delta,
	life_time
);

}
}
}
}

#endif
