#ifndef SANGUIS_CLIENT_WEAPON_ATTRIBUTE_TOTAL_HPP_INCLUDED
#define SANGUIS_CLIENT_WEAPON_ATTRIBUTE_TOTAL_HPP_INCLUDED

#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_value.hpp>


namespace sanguis::client
{

sanguis::weapon_attribute_value
weapon_attribute_total(
	sanguis::weapon_attribute_base,
	sanguis::weapon_attribute_extra
);

}

#endif
