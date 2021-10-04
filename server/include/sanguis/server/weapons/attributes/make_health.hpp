#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_MAKE_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_MAKE_HEALTH_HPP_INCLUDED

#include <sanguis/weapon_attribute_fwd.hpp>
#include <sanguis/server/weapons/attributes/health_fwd.hpp>


namespace sanguis::server::weapons::attributes
{

sanguis::weapon_attribute
make_health(
	sanguis::server::weapons::attributes::health const &
);

}

#endif
