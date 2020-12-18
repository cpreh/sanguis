#ifndef SANGUIS_SERVER_DAMAGE_ARMOR_META_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARMOR_META_FWD_HPP_INCLUDED

#include <sanguis/server/damage/armor_unit_fwd.hpp>
#include <sanguis/server/damage/basic_meta_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

using
armor_meta
=
sanguis::server::damage::basic_meta<
	sanguis::server::damage::armor_unit
>;

}
}
}

#endif
