#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_PRIMARY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_PRIMARY_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>


namespace sanguis::server::weapons::factory
{

sanguis::server::weapons::unique_ptr
primary(
	sanguis::primary_weapon_type,
	sanguis::server::weapons::factory::parameters const &
);

}

#endif
