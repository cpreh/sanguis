#ifndef SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED

#include "auto_ptr.hpp"
#include "../../weapon_type.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

auto_ptr
create(
	weapon_type::type
);

}
}
}

#endif
