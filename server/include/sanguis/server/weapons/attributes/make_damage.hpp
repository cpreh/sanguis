#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_MAKE_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_MAKE_DAMAGE_HPP_INCLUDED

#include <sanguis/weapon_attribute_fwd.hpp>
#include <sanguis/server/weapons/attributes/damage_fwd.hpp>


namespace sanguis::server::weapons::attributes
{

sanguis::weapon_attribute
make_damage(
	sanguis::server::weapons::attributes::damage const &
);

}

#endif
