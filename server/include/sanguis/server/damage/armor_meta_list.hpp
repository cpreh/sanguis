#ifndef SANGUIS_SERVER_DAMAGE_ARMOR_META_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARMOR_META_LIST_HPP_INCLUDED

#include <sanguis/server/damage/armor_unit.hpp>
#include <sanguis/server/damage/basic_meta_list.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

using
armor_meta_list
=
sanguis::server::damage::basic_meta_list<
	sanguis::server::damage::armor_unit
>;

}
}
}

#endif
