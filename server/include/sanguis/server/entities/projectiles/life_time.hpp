#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_LIFE_TIME_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_LIFE_TIME_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::entities::projectiles
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	life_time
);

}

#endif
