#ifndef SANGUIS_SERVER_DAMAGE_ARMOR_LIST_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARMOR_LIST_FWD_HPP_INCLUDED

#include <sanguis/server/damage/armor_unit_fwd.hpp>
#include <sanguis/server/damage/basic_list_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

typedef
sanguis::server::damage::basic_list<
	sanguis::server::damage::armor_unit
>
armor_list;

}
}
}

#endif
