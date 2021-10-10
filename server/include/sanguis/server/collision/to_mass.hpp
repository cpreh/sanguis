#ifndef SANGUIS_SERVER_COLLISION_TO_MASS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_TO_MASS_HPP_INCLUDED

#include <sanguis/collision/mass.hpp>
#include <sanguis/server/mass_fwd.hpp>

namespace sanguis::server::collision
{

sanguis::collision::mass to_mass(sanguis::server::mass const &);

}

#endif
