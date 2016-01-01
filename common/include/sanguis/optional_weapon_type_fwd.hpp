#ifndef SANGUIS_OPTIONAL_WEAPON_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_OPTIONAL_WEAPON_TYPE_FWD_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{

typedef
fcppt::optional::object<
	sanguis::weapon_type
>
optional_weapon_type;

}

#endif
