#ifndef SANGUIS_SERVER_DAMAGE_ARMOR_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARMOR_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/server/damage/armor_unit_fwd.hpp>
#include <sanguis/server/damage/basic_array_fwd.hpp>

namespace sanguis::server::damage
{

using armor_array = sanguis::server::damage::basic_array<sanguis::server::damage::armor_unit>;

}

#endif
