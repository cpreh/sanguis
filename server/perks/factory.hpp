#ifndef SANGUIS_SERVER_PERKS_FACTORY_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_FACTORY_HPP_INCLUDED

#include "auto_ptr.hpp"
#include "../../perk_type.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

auto_ptr
create(
	perk_type::type);	

}
}
}

#endif
