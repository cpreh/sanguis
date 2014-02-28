#ifndef SANGUIS_MODEL_AUX__DESERIALIZE_WEAPON_CATEGORY_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__DESERIALIZE_WEAPON_CATEGORY_MAP_HPP_INCLUDED

#include <sanguis/model/weapon_category_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace deserialize
{

sanguis::model::weapon_category_map
weapon_category_map(
	sge::parse::json::object const &
);

}
}
}
}

#endif
