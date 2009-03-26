#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_HPP_INCLUDED

#include "auto_ptr.hpp"
#include "../environment_fwd.hpp"
#include "../../weapon_type.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

auto_ptr
create(
	weapon_type::type,
	environment const &);

}
}
}

#endif
