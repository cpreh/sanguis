#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_LIFE_TIME_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_LIFE_TIME_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::entities::projectiles
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::duration, life_time);

}

#endif
