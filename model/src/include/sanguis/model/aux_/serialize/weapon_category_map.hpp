#ifndef SANGUIS_MODEL_AUX__SERIALIZE_WEAPON_CATEGORY_MAP_HPP_INCLUDED
#define SANGUIS_MODEL_AUX__SERIALIZE_WEAPON_CATEGORY_MAP_HPP_INCLUDED

#include <sanguis/model/weapon_category_map.hpp>
#include <sge/parse/json/member.hpp>


namespace sanguis
{
namespace model
{
namespace aux_
{
namespace serialize
{

sge::parse::json::member
weapon_category_map(
	sanguis::model::weapon_category_map const &
);

}
}
}
}

#endif
