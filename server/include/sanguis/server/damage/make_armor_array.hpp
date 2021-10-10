#ifndef SANGUIS_SERVER_DAMAGE_MAKE_ARMOR_ARRAY_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_MAKE_ARMOR_ARRAY_HPP_INCLUDED

#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/armor_meta_list.hpp>

namespace sanguis::server::damage
{

sanguis::server::damage::armor_array
make_armor_array(sanguis::server::damage::armor_meta_list const &);

}

#endif
