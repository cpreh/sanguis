#ifndef SANGUIS_WEAPON_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_WEAPON_TYPE_FWD_HPP_INCLUDED

#include <sanguis/weapon_types_fwd.hpp>
#include <fcppt/variant/from_list_fwd.hpp>


namespace sanguis
{

typedef
fcppt::variant::from_list<
	sanguis::weapon_types
>
weapon_type;

}

#endif
