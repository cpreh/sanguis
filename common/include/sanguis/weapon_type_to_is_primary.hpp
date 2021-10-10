#ifndef SANGUIS_WEAPON_TYPE_TO_IS_PRIMARY_HPP_INCLUDED
#define SANGUIS_WEAPON_TYPE_TO_IS_PRIMARY_HPP_INCLUDED

#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/common/symbol.hpp>

namespace sanguis
{

SANGUIS_COMMON_SYMBOL
sanguis::is_primary_weapon weapon_type_to_is_primary(sanguis::weapon_type const &);

}

#endif
