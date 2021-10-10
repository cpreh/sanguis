#ifndef SANGUIS_SERVER_ENTITIES_MODIFY_DAMAGES_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_MODIFY_DAMAGES_HPP_INCLUDED

#include <sanguis/server/damage/array_fwd.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/entities/ifaces/with_weapon_fwd.hpp>

namespace sanguis::server::entities
{

sanguis::server::damage::modified_array modify_damages(
    sanguis::server::entities::ifaces::with_weapon const &, sanguis::server::damage::array const &);

}

#endif
