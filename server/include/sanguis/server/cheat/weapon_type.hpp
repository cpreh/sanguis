#ifndef SANGUIS_SERVER_CHEAT_WEAPON_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_CHEAT_WEAPON_TYPE_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/optional_weapon_type.hpp>


namespace sanguis::server::cheat
{

sanguis::optional_weapon_type
weapon_type(
	sanguis::cheat_type
);

}

#endif
