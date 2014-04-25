#ifndef SANGUIS_CLIENT_LOAD_MODEL_LOOKUP_WEAPON_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_LOOKUP_WEAPON_NAME_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/model/weapon_category_name_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

sanguis::optional_primary_weapon_type const
lookup_weapon_name(
	sanguis::model::weapon_category_name const &
);

}
}
}
}

#endif
