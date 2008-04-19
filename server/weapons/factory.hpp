#ifndef SANGUIS_SERVER_WEAPONS_FACTORY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_FACTORY_HPP_INCLUDED

#include "../../weapon_type.hpp"
#include "weapon.hpp"
#include <memory>

namespace sanguis
{
namespace server
{
namespace weapons
{

typedef std::auto_ptr<weapon> weapon_ptr;

weapon_ptr create(weapon_type::type);

}
}
}

#endif
