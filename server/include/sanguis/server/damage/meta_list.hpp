#ifndef SANGUIS_SERVER_DAMAGE_META_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_META_LIST_HPP_INCLUDED

#include <sanguis/server/damage/basic_meta_list.hpp>
#include <sanguis/server/damage/unit.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

using
meta_list
=
sanguis::server::damage::basic_meta_list<
	sanguis::server::damage::unit
>;

}
}
}

#endif
