#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_HPP_INCLUDED

#include "../environment_fwd.hpp"
#include "../../weapon_type.hpp"
#include "weapon.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

weapon_ptr create(
	weapon_type::type,
	environment const &);

}
}
}

#endif
