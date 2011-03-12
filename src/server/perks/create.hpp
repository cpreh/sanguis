#ifndef SANGUIS_SERVER_PERKS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CREATE_HPP_INCLUDED

#include "unique_ptr.hpp"
#include "../../perk_type.hpp"

namespace sanguis
{
namespace server
{
namespace perks
{

unique_ptr
create(
	perk_type::type
);

}
}
}

#endif
