#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_HPP_INCLUDED

#include "../../weapon_type.hpp"
#include "../insert_callback.hpp"
#include "../send_callback.hpp"
#include "weapon.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

weapon_ptr create(
	weapon_type::type,
	send_callback,
	insert_callback);

}
}
}

#endif
