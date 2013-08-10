#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_SECONDARY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_SECONDARY_HPP_INCLUDED

#include <sanguis/secondary_weapon_type_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace factory
{

sanguis::server::weapons::unique_ptr
secondary(
	sanguis::secondary_weapon_type,
	sanguis::server::weapons::factory::parameters const &
);

}
}
}
}

#endif
