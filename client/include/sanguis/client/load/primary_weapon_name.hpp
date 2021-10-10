#ifndef SANGUIS_CLIENT_LOAD_PRIMARY_WEAPON_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_PRIMARY_WEAPON_NAME_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp>
#include <sanguis/model/weapon_category_name.hpp>

namespace sanguis::client::load
{

sanguis::model::weapon_category_name primary_weapon_name(sanguis::primary_weapon_type);

}

#endif
