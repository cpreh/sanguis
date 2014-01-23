#ifndef SANGUIS_OPTIONAL_WEAPON_ATTRIBUTE_VALUE_FWD_HPP_INCLUDED
#define SANGUIS_OPTIONAL_WEAPON_ATTRIBUTE_VALUE_FWD_HPP_INCLUDED

#include <sanguis/weapon_attribute_value.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{

typedef
fcppt::optional<
	sanguis::weapon_attribute_value
>
optional_weapon_attribute_value;

}

#endif
