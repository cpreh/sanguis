#ifndef SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED

#include "unique_ptr.hpp"
#include "../../weapon_type.hpp"

namespace sanguis
{
namespace server
{
namespace weapons
{

unique_ptr
create(
	weapon_type::type
);

}
}
}

#endif
