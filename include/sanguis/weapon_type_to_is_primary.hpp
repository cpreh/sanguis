#ifndef SANGUIS_WEAPON_TYPE_TO_IS_PRIMARY_HPP_INCLUDED
#define SANGUIS_WEAPON_TYPE_TO_IS_PRIMARY_HPP_INCLUDED

#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/weapon_type_fwd.hpp>


namespace sanguis
{

sanguis::is_primary_weapon const
weapon_type_to_is_primary(
	sanguis::weapon_type const &
);

}

#endif
