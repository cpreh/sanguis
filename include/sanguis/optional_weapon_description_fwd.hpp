#ifndef SANGUIS_OPTIONAL_WEAPON_DESCRIPTION_FWD_HPP_INCLUDED
#define SANGUIS_OPTIONAL_WEAPON_DESCRIPTION_FWD_HPP_INCLUDED

#include <sanguis/weapon_description_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{

typedef
fcppt::optional<
	sanguis::weapon_description
>
optional_weapon_description;

}

#endif
