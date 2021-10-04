#ifndef SANGUIS_SERVER_DAMAGE_ARMOR_UNIT_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARMOR_UNIT_FWD_HPP_INCLUDED

#include <sanguis/server/damage/unit_value.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis::server::damage
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::damage::unit_value,
	armor_unit
);

}

#endif
