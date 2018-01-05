#ifndef SANGUIS_WEAPON_TYPES_FWD_HPP_INCLUDED
#define SANGUIS_WEAPON_TYPES_FWD_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp>
#include <sanguis/secondary_weapon_type_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

typedef
brigand::list<
	sanguis::primary_weapon_type,
	sanguis::secondary_weapon_type
>
weapon_types;

}

#endif
