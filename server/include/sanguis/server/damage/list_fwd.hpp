#ifndef SANGUIS_SERVER_DAMAGE_LIST_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_LIST_FWD_HPP_INCLUDED

#include <sanguis/server/damage/basic_list_fwd.hpp>
#include <sanguis/server/damage/unit_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

typedef
sanguis::server::damage::basic_list<
	sanguis::server::damage::unit
>
list;

}
}
}

#endif
