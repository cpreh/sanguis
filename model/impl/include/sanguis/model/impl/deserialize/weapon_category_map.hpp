#ifndef SANGUIS_MODEL_IMPL_DESERIALIZE_WEAPON_CATEGORY_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_IMPL_DESERIALIZE_WEAPON_CATEGORY_MAP_HPP_INCLUDED

#include <sanguis/model/weapon_category_map.hpp>
#include <sge/parse/json/object_fwd.hpp>


namespace sanguis::model::impl::deserialize
{

sanguis::model::weapon_category_map
weapon_category_map(
	sge::parse::json::object const &
);

}

#endif
